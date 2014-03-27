#ifndef RANDOMSAMPLING_NEWGENE_H
#define RANDOMSAMPLING_NEWGENE_H

#include <cstdint>
#include <vector>
#include <set>
#include <map>
#ifndef Q_MOC_RUN
#	include <boost/multiprecision/cpp_int.hpp>
#	include <boost/variant.hpp>
#endif
#include "../../Utilities/NewGeneException.h"
#include "../../sqlite/sqlite-amalgamation-3071700/sqlite3.h"

typedef boost::variant<std::int64_t, double, std::string> InstanceData;
typedef boost::variant<std::int64_t, double, std::string> DMUInstanceData;
typedef boost::variant<std::int64_t, double, std::string> SecondaryInstanceData;

typedef std::vector<DMUInstanceData> DMUInstanceDataVector;
typedef std::vector<SecondaryInstanceData> SecondaryInstanceDataVector;

typedef std::map<std::int64_t, SecondaryInstanceDataVector> DataCache;

class TimeSlice
{

	public:

		TimeSlice()
			: time_start{ 0 }
			, time_end  { 0 }
		{}

		TimeSlice(std::int64_t time_start_, std::int64_t time_end_)
			: time_start{ time_start_ }
			, time_end{ time_end_ }
		{}

		TimeSlice(TimeSlice const & rhs)
			: time_start{ rhs.time_start }
			, time_end  { rhs.time_end }
		{}

		std::int64_t Width() const
		{
			return time_end - time_start;
		}

		TimeSlice & operator=(TimeSlice const & rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			time_start = rhs.time_start;
			time_end = rhs.time_end;
			return *this;
		}

		void Reshape(std::int64_t const & new_start, std::int64_t const & new_end)
		{
			time_start = new_start;
			time_end = new_end;
		}

		bool operator<(TimeSlice const & rhs) const
		{
			if (time_start < rhs.time_start)
			{
				return true;
			}
			else
			if (time_end < rhs.time_end)
			{
				return true;
			}
			return false;
		}

		inline bool Validate() const
		{
			if (time_end <= time_start)
			{
				return false;
			}
			return true;
		}

		inline bool IsEndTimeGreaterThanRhsStartTime(TimeSlice const & rhs) const
		{
			if (time_end > rhs.time_start)
			{
				return true;
			}
			return false;
		}

		std::int64_t time_start;
		std::int64_t time_end;

};

class Weighting
{

	public:

		Weighting()
			: weighting{ 0 }
			, weighting_range_start{ 0 }
			, weighting_range_end{ 0 }
		{}

		Weighting(Weighting const & rhs)
			: weighting{ rhs.weighting }
			, weighting_range_start{ rhs.weighting_range_start }
			, weighting_range_end{ rhs.weighting_range_end }
		{}

		Weighting & operator=(Weighting const & rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			weighting = rhs.weighting;
			weighting_range_start = rhs.weighting_range_start;
			weighting_range_end = rhs.weighting_range_end;
			return *this;
		}

		boost::multiprecision::cpp_int weighting;
		boost::multiprecision::cpp_int weighting_range_start;
		boost::multiprecision::cpp_int weighting_range_end;

};

class PrimaryKeysGrouping
{

	public:

		PrimaryKeysGrouping(DMUInstanceDataVector const & dmuInstanceDataVector)
			: primary_keys(dmuInstanceDataVector)
		{}

		PrimaryKeysGrouping(PrimaryKeysGrouping const & rhs)
			: primary_keys(rhs.primary_keys)
		{}

		PrimaryKeysGrouping & operator=(PrimaryKeysGrouping const & rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			primary_keys = rhs.primary_keys;
			return *this;
		}

		PrimaryKeysGrouping & operator=(PrimaryKeysGrouping const && rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			primary_keys = std::move(rhs.primary_keys);
		}

		DMUInstanceDataVector primary_keys;

		bool operator<(PrimaryKeysGrouping const & rhs) const
		{

			if (primary_keys.size() != rhs.primary_keys.size())
			{
				boost::format msg("Number of DMU's is different in PrimaryKeysGrouping::operator<()!");
				throw NewGeneException() << newgene_error_description(msg.str());
			}

			size_t nDmus = primary_keys.size();
			for (size_t n = 0; n < nDmus; ++n)
			{
				bool is_current_less_than = boost::apply_visitor(less_than_visitor(), primary_keys[n], rhs.primary_keys[n]);
				if (is_current_less_than)
				{
					return true;
				}
				else
				{
					bool is_current_greater_than = boost::apply_visitor(less_than_visitor(), rhs.primary_keys[n], primary_keys[n]);
					if (is_current_greater_than)
					{
						return false;
					}
					else
					{
						// so far, equal; continue
					}
				}
			}

			// equal in all DMU's, so return false
			return false;

		}

	protected:

		class less_than_visitor : public boost::static_visitor<bool>
		{

		public:

			template <typename T, typename U>
			bool operator()(const T &, const U &) const
			{
				boost::format msg("DMU's are of different types in PrimaryKeysGrouping::less_than_visitor()!");
				throw NewGeneException() << newgene_error_description(msg.str());
			}

			template <typename T>
			bool operator()(T const & lhs, T const & rhs)
			{
				return lhs < rhs;
			}

		};

};

// "Leaf"
class PrimaryKeysGroupingMultiplicityGreaterThanOne : public PrimaryKeysGrouping
{

	public:

		PrimaryKeysGroupingMultiplicityGreaterThanOne()
			: PrimaryKeysGrouping{ DMUInstanceDataVector() }
			, index_into_raw_data{ 0 }
		{}

		PrimaryKeysGroupingMultiplicityGreaterThanOne(DMUInstanceDataVector const & dmuInstanceDataVector, std::int64_t const & index_into_raw_data_)
			: PrimaryKeysGrouping(dmuInstanceDataVector)
			, index_into_raw_data{ index_into_raw_data_ }
		{}

		PrimaryKeysGroupingMultiplicityGreaterThanOne(PrimaryKeysGroupingMultiplicityGreaterThanOne const & rhs)
			: PrimaryKeysGrouping(rhs)
			, index_into_raw_data{ rhs.index_into_raw_data }
		{}

		PrimaryKeysGroupingMultiplicityGreaterThanOne & operator=(PrimaryKeysGroupingMultiplicityGreaterThanOne const & rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			PrimaryKeysGrouping::operator=(rhs);
			index_into_raw_data = rhs.index_into_raw_data;
			return *this;
		}

		PrimaryKeysGroupingMultiplicityGreaterThanOne & operator=(PrimaryKeysGroupingMultiplicityGreaterThanOne const && rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			PrimaryKeysGrouping::operator=(std::move(rhs));
			index_into_raw_data = rhs.index_into_raw_data;
		}

		std::int64_t index_into_raw_data;

};

// "Branch"
class PrimaryKeysGroupingMultiplicityOne : public PrimaryKeysGrouping
{

	public:

		PrimaryKeysGroupingMultiplicityOne()
			: PrimaryKeysGrouping{ DMUInstanceDataVector() }
			, number_branch_combinations{ 0 }
		{}

		PrimaryKeysGroupingMultiplicityOne(DMUInstanceDataVector const & dmuInstanceDataVector)
			: PrimaryKeysGrouping(dmuInstanceDataVector)
			, number_branch_combinations{ 0 }
		{}

		PrimaryKeysGroupingMultiplicityOne(PrimaryKeysGroupingMultiplicityOne const & rhs)
			: PrimaryKeysGrouping(rhs)
			, weighting{ rhs.weighting }
			, hit{ rhs.hit }
			, remaining{ rhs.remaining }
			, number_branch_combinations{rhs.number_branch_combinations}
		{}

		PrimaryKeysGroupingMultiplicityOne & operator=(PrimaryKeysGroupingMultiplicityOne const & rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			PrimaryKeysGrouping::operator=(rhs);
			weighting = rhs.weighting;
			hit = rhs.hit;
			remaining = rhs.remaining;
			number_branch_combinations = rhs.number_branch_combinations;
			return *this;
		}

		PrimaryKeysGroupingMultiplicityOne & operator=(PrimaryKeysGroupingMultiplicityOne const && rhs)
		{
			if (&rhs == this)
			{
				return *this;
			}
			PrimaryKeysGrouping::operator=(std::move(rhs));
			weighting = rhs.weighting;
			hit = rhs.hit;
			remaining = rhs.remaining;
			number_branch_combinations = rhs.number_branch_combinations;
		}

		mutable Weighting weighting; // Weighting for this branch: This is the lowest-level, calculated value

		mutable std::set<std::set<int>> hit; // cache of leaf combinations already hit
		mutable std::vector<std::set<int>> remaining;
		mutable boost::multiprecision::cpp_int number_branch_combinations;

};

typedef PrimaryKeysGroupingMultiplicityGreaterThanOne Leaf;
typedef std::set<Leaf> Leaves;
typedef PrimaryKeysGroupingMultiplicityOne Branch;
typedef std::map<Branch, Leaves> BranchesAndLeaves;

class VariableGroupBranchesAndLeaves
{

	public:

		VariableGroupBranchesAndLeaves(int const & variable_group_number_)
			: variable_group_number(variable_group_number_)
		{}

		int variable_group_number;
		BranchesAndLeaves branches_and_leaves;
		Weighting weighting; // sum over all branches and leaves

		//bool operator==(VariableGroupBranchesAndLeaves const & rhs) const
		bool operator==(int const & rhs) const
		{
			//if (variable_group_name == rhs.variable_group_name)
			if (variable_group_number == rhs)
			{
				return true;
			}
			return false;
		}

};

typedef std::vector<VariableGroupBranchesAndLeaves> VariableGroupBranchesAndLeavesVector;

class VariableGroupTimeSliceData
{

	public:

		VariableGroupBranchesAndLeavesVector branches_and_leaves;
		Weighting weighting; // sum over all branches and leaves in all variable groups

};

typedef std::map<TimeSlice, VariableGroupTimeSliceData> TimeSlices;

typedef std::pair<TimeSlice, Leaf> TimeSliceLeaf;

class AllWeightings
{

	public:

		AllWeightings();
		~AllWeightings();

		TimeSlices timeSlices;
		DataCache dataCache; // caches secondary key data required to create final results in a fashion that can be migrated (partially) to disk via LIFO to support huge monadic input datasets used in the construction of kads
		Weighting weighting; // sum over all time slices

		sqlite3_stmt * insert_random_sample_stmt;

		void HandleBranchAndLeaf(Branch const & branch, TimeSliceLeaf & timeSliceLeaf, int const & variable_group_number);
		void CalculateWeightings(int const K);
		void PrepareRandomNumbers(int how_many);
		bool RetrieveNextBranchAndLeaves(int const K, Branch & branch, Leaves & leaves, TimeSlice & time_slice);
		void PopulateAllLeafCombinations(int const K, Branch const & branch, Leaves const & leaves);

	protected:

		bool HandleTimeSliceNormalCase(Branch const & branch, TimeSliceLeaf & timeSliceLeaf, TimeSlices::iterator & mapElementPtr, int const & variable_group_number);

		void AddNewTimeSlice(int const & variable_group_number, Branch const & branch, TimeSliceLeaf const &newTimeSliceLeaf);

		// Breaks an existing map entry into two pieces and returns an iterator to both.
		void SliceMapEntry(TimeSlices::iterator const & existingMapElementPtr, std::int64_t const middle, TimeSlices::iterator & newMapElementLeftPtr, TimeSlices::iterator & newMapElementRightPtr);

		// Breaks an existing map entry into three pieces and returns an iterator to the middle piece.
		void SliceMapEntry(TimeSlices::iterator const & existingMapElementPtr, std::int64_t const left, std::int64_t const right, TimeSlices::iterator & newMapElementMiddlePtr);

		// Slices off the left part of the "incoming_slice" TimeSliceLeaf and returns it in the "new_left_slice" TimeSliceLeaf.
		// The "incoming_slice" TimeSliceLeaf is adjusted to become equal to the remaining part on the right.
		void SliceOffLeft(TimeSliceLeaf & incoming_slice, std::int64_t const slicePoint, TimeSliceLeaf & new_left_slice);

		// Merge time slice data into a map element
		void MergeTimeSliceDataIntoMap(Branch const & branch, TimeSliceLeaf const & timeSliceLeaf, TimeSlices::iterator & mapElementPtr, int const & variable_group_number);

		Leaves GetLeafCombination(int const K, Branch const & branch, Leaves const & leaves);

		static bool is_map_entry_end_time_greater_than_new_time_slice_start_time(TimeSliceLeaf const & new_time_slice_ , TimeSlices::value_type const & map_entry_)
		{

			TimeSlice const & new_time_slice = new_time_slice_.first;
			TimeSlice const & map_entry = map_entry_.first;

			return map_entry.IsEndTimeGreaterThanRhsStartTime(new_time_slice);

		}

		std::set<boost::multiprecision::cpp_int> random_numbers;
		std::set<boost::multiprecision::cpp_int>::const_iterator random_number_iterator;

	private:

		void AddPositionToRemaining(std::vector<int> const & position, Branch const & branch);
		bool IncrementPosition(int const K, std::vector<int> & position, Leaves const & leaves);
		int IncrementPositionManageSubK(int const K, int const subK, std::vector<int> & position, Leaves const & leaves);

		boost::multiprecision::cpp_int BinomialCoefficient(int const N, int const K);

};

#endif
