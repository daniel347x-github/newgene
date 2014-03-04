#include "Validation.h"

#ifndef Q_MOC_RUN
#	include <boost/algorithm/string.hpp>
#	include <boost/regex.hpp>
#	include <boost/format.hpp>
#	include <boost/lexical_cast.hpp>
#	include "boost/date_time/gregorian/gregorian.hpp"
#endif

bool Validation::ValidateDmuMemberUUID(std::string & proposed_dmu_member_uuid, std::string & errorMsg)
{

	boost::trim(proposed_dmu_member_uuid);

	if (proposed_dmu_member_uuid.empty())
	{
		boost::format msg("The DMU member you entered is empty.");
		errorMsg = msg.str();
		return false;
	}

	std::string regex_string_uuid("([a-zA-Z_0-9]*)");
	boost::regex regex_uuid(regex_string_uuid);
	boost::cmatch matches_uuid;

	bool valid = false;
	std::string invalid_string;
	if (boost::regex_match(proposed_dmu_member_uuid.c_str(), matches_uuid, regex_uuid))
	{
		// matches[0] contains the original string.  matches[n]
		// contains a sub_match object for each matching
		// subexpression
		// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
		// for an example usage
		if (matches_uuid.size() == 2)
		{
			std::string the_dmu_member_uuid_match(matches_uuid[1].first, matches_uuid[1].second);

			if (the_dmu_member_uuid_match.size() <= 36)
			{
				if (the_dmu_member_uuid_match == proposed_dmu_member_uuid)
				{
					valid = true;
				}
			}
			else
			{
				invalid_string = ": The length is too long (maximum length: 36).";
			}

		}
	}

	if (!valid)
	{
		boost::format msg("The DMU member code you entered is invalid%1%");
		msg % invalid_string;
		errorMsg = msg.str();
	}

	return valid;

}

bool Validation::ValidateDmuMemberCode(std::string & proposed_dmu_member_code, std::string & errorMsg)
{

	boost::trim(proposed_dmu_member_code);

	std::string regex_string_code("([a-zA-Z_0-9]*)");
	boost::regex regex_code(regex_string_code);
	boost::cmatch matches_code;

	bool valid = true;
	if (valid && boost::regex_match(proposed_dmu_member_code.c_str(), matches_code, regex_code))
	{
		// matches[0] contains the original string.  matches[n]
		// contains a sub_match object for each matching
		// subexpression
		// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
		// for an example usage
		if (valid && matches_code.size() == 2)
		{
			std::string the_dmu_member_code_match(matches_code[1].first, matches_code[1].second);

			if (valid && the_dmu_member_code_match == proposed_dmu_member_code)
			{
				 // no-op
			}
			else
			{
				boost::format msg("The abbreviation is invalid.");
				errorMsg = msg.str();
				valid = false;
			}

		}
		else
		{
			boost::format msg("The abbreviation is invalid.");
			errorMsg = msg.str();
			valid = false;
		}
	}

	if (valid)
	{
		if (valid && proposed_dmu_member_code.size() > 128)
		{
			boost::format msg("The abbreviation is too long (maximum length: 128).");
			errorMsg = msg.str();
			valid = false;
		}
	}

	return valid;

}

bool Validation::ValidateDmuMemberDescription(std::string & proposed_dmu_member_description, std::string & errorMsg)
{

	boost::trim(proposed_dmu_member_description);

	bool valid = true;
	if (proposed_dmu_member_description.size() > 4096)
	{
		boost::format msg("The description is too long (maximum length: 4096).");
		errorMsg = msg.str();
		valid = false;
	}

	return valid;

}

bool Validation::ValidateDmuDescription(std::string & proposed_dmu_description, std::string & errorMsg)
{

	boost::trim(proposed_dmu_description);

	bool valid = true;
	if (proposed_dmu_description.size() > 4096)
	{
		boost::format msg("The description is too long (maximum length: 4096).");
		errorMsg = msg.str();
		valid = false;
	}

	return valid;

}

bool Validation::ValidateColumnName(std::string & proposed_column_name, std::string const & column_description_for_invalid_message, bool const required, std::string & errorMsg)
{

	boost::trim(proposed_column_name);

	bool valid = true;

	if (valid)
	{
		if (proposed_column_name.empty())
		{
			if (required)
			{
				boost::format msg("The '%1%' column name cannot be empty.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
				valid = false;
			}
		}
	}

	if (valid)
	{
		if (proposed_column_name.size() > 1024)
		{
			boost::format msg("The '%1%' column name is too long.");
			msg % column_description_for_invalid_message;
			errorMsg = msg.str();
			valid = false;
		}

	}

	if (valid)
	{

		std::string regex_string("([a-zA-Z_0-9]*)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		if (boost::regex_match(proposed_column_name.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid && the_match == proposed_column_name)
				{
					// no-op
				}
				else
				{
					boost::format msg("The '%1%' column name is invalid.");
					msg % column_description_for_invalid_message;
					errorMsg = msg.str();
					valid = false;
				}

			}
			else
			{
				boost::format msg("The '%1%' column name is invalid.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
				valid = false;
			}
		}

	}

	return valid;

}

bool Validation::ValidateDmuCode(std::string & proposed_dmu_code, std::string & errorMsg)
{

	boost::trim(proposed_dmu_code);

	bool valid = true;

	if (valid)
	{
		if (proposed_dmu_code.empty())
		{
			boost::format msg("The DMU code cannot be empty.");
			errorMsg = msg.str();
			valid = false;
		}
	}

	if (valid)
	{
		if (proposed_dmu_code.size() > 128)
		{
			boost::format msg("The DMU code is too long (maximum length: 128).");
			errorMsg = msg.str();
			valid = false;
		}

	}

	if (valid)
	{

		std::string regex_string("([a-zA-Z]+)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		if (boost::regex_match(proposed_dmu_code.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid && the_match == proposed_dmu_code)
				{
					// no-op
				}
				else
				{
					boost::format msg("The DMU code is invalid.  Only letters are allowed.");
					errorMsg = msg.str();
					valid = false;
				}

			}
			else
			{
				boost::format msg("The DMU code is invalid.");
				errorMsg = msg.str();
				valid = false;
			}
		}

	}

	return valid;

}

bool Validation::ValidateUoaCode(std::string & proposed_uoa_code, std::string & errorMsg)
{

	boost::trim(proposed_uoa_code);

	bool valid = true;

	if (valid)
	{
		if (proposed_uoa_code.empty())
		{
			boost::format msg("The UOA code cannot be empty.");
			errorMsg = msg.str();
			valid = false;
		}
	}

	if (valid)
	{
		if (proposed_uoa_code.size() > 128)
		{
			boost::format msg("The UOA code is too long (maximum length: 128).");
			errorMsg = msg.str();
			valid = false;
		}

	}

	if (valid)
	{

		std::string regex_string("([a-zA-Z]+)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		if (boost::regex_match(proposed_uoa_code.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid && the_match == proposed_uoa_code)
				{
					// no-op
				}
				else
				{
					boost::format msg("The UOA code is invalid.  Only letters are allowed.");
					errorMsg = msg.str();
					valid = false;
				}

			}
			else
			{
				boost::format msg("The UOA code is invalid.");
				errorMsg = msg.str();
				valid = false;
			}
		}

	}

	return valid;

}

bool Validation::ValidateYearInteger(std::string & proposed_year_integer, short & theYear, std::string const & column_description_for_invalid_message, bool const required, std::string & errorMsg)
{

	boost::trim(proposed_year_integer);

	bool valid = true;

	if (valid)
	{
		if (proposed_year_integer.empty())
		{
			if (required)
			{
				boost::format msg("The '%1%' cannot be empty.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
				valid = false;
			}
		}
	}

	if (valid)
	{

		std::string regex_string("([0-9]*)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		valid = false;
		if (boost::regex_match(proposed_year_integer.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid)
				{

					try
					{
						std::string the_year_string(matches[1].first, matches[1].second);
						theYear = boost::lexical_cast<short>(the_year_string);

						if (theYear >= 1752 && theYear <= 3000)
						{
							valid = true;
						}

					}
					catch (boost::bad_lexical_cast &)
					{
						// no-op
					}

				}

				if (!valid)
				{
					boost::format msg("The '%1%' is invalid.  It must be an integer between 1752 and 3000.");
					msg % column_description_for_invalid_message;
					errorMsg = msg.str();
				}

			}
			else
			{
				boost::format msg("The '%1%' column name is invalid.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
			}
		}

	}

	return valid;

}

bool Validation::ValidateMonthInteger(std::string & proposed_month_integer, short & theMonth, std::string const & column_description_for_invalid_message, bool const required, std::string & errorMsg)
{

	boost::trim(proposed_month_integer);

	bool valid = true;

	if (valid)
	{
		if (proposed_month_integer.empty())
		{
			if (required)
			{
				boost::format msg("The '%1%' cannot be empty.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
				valid = false;
			}
		}
	}

	if (valid)
	{

		std::string regex_string("([0-9]*)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		valid = false;
		if (boost::regex_match(proposed_month_integer.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid)
				{

					try
					{
						std::string the_month_string(matches[1].first, matches[1].second);
						theMonth = boost::lexical_cast<short>(the_month_string);
						if (theMonth >= 1 && theMonth <= 12)
						{
							valid = true;
						}
					}
					catch (boost::bad_lexical_cast &)
					{
						// no-op
					}

				}

				if (!valid)
				{
					boost::format msg("The '%1%' is invalid.  It must be an integer between 1 and 12.");
					msg % column_description_for_invalid_message;
					errorMsg = msg.str();
				}

			}
			else
			{
				boost::format msg("The '%1%' column name is invalid.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
			}
		}

	}

	return valid;

}

bool Validation::ValidateDayInteger(short const theYear, short const theMonth, std::string & proposed_day_integer, short & theDay, std::string const & column_description_for_invalid_message, bool const required, std::string & errorMsg)
{

	boost::trim(proposed_day_integer);

	bool valid = true;

	if (valid)
	{
		if (proposed_day_integer.empty())
		{
			if (required)
			{
				boost::format msg("The '%1%' cannot be empty.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
				valid = false;
			}
		}
	}

	if (valid)
	{

		std::string regex_string("([0-9]*)");
		boost::regex regex(regex_string);
		boost::cmatch matches;

		valid = false;

		if (boost::regex_match(proposed_day_integer.c_str(), matches, regex))
		{
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			// ... see http://www.onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html?page=3
			// for an example usage
			if (valid && matches.size() == 2)
			{
				std::string the_match(matches[1].first, matches[1].second);

				if (valid)
				{

					try
					{

						std::string the_day_string(matches[1].first, matches[1].second);
						theDay = boost::lexical_cast<short>(the_day_string);
						boost::gregorian::greg_year y(theYear);
						boost::gregorian::greg_month m(theMonth);
						boost::gregorian::greg_day d(theDay);
						boost::gregorian::date ymd(y, m, d);
						boost::gregorian::date lastday = ymd.end_of_month();

						if (lastday.day() >= theDay)
						{
							valid = true;
						}

					}
					catch (boost::bad_lexical_cast &)
					{
						// no-op
					}
					catch (boost::gregorian::bad_year &)
					{
						// no-op
					}
					catch (boost::gregorian::bad_month &)
					{
						// no-op
					}
					catch (boost::gregorian::bad_day_of_month &)
					{
						// no-op
					}

				}

				if (!valid)
				{
					boost::format msg("The '%1%' is invalid.");
					msg % column_description_for_invalid_message;
					errorMsg = msg.str();
				}

			}
			else
			{
				boost::format msg("The '%1%' column name is invalid.");
				msg % column_description_for_invalid_message;
				errorMsg = msg.str();
			}
		}

	}

	return valid;

}

bool Validation::ValidateDate1beforeDate2(short const y1, short const m1, short const d1, short const y2, short const m2, short const d2, std::string & errMsg)
{
	try
	{

		boost::gregorian::date ymd1(y1, m1, d1);
		boost::gregorian::date ymd2(y2, m2, d2);

		if (ymd1 <= ymd2)
		{
			return true;
		}

	}
	catch (boost::bad_lexical_cast &)
	{
		// no-op
	}
	catch (boost::gregorian::bad_year &)
	{
		// no-op
	}
	catch (boost::gregorian::bad_month &)
	{
		// no-op
	}
	catch (boost::gregorian::bad_day_of_month &)
	{
		// no-op
	}

	boost::format msg("The start date is later than the end date.");
	errMsg = msg.str();

	return false;

}

bool Validation::ValidateDatePair(std::string & y1, std::string & m1, std::string & d1, std::string & y2, std::string & m2, std::string & d2, std::string & errorMsg)
{

	bool valid = false;

	short ymd_yStart = 0;
	short ymd_yEnd = 0;
	short ymd_mStart = 0;
	short ymd_mEnd = 0;
	short ymd_dStart = 0;
	short ymd_dEnd = 0;

	if (valid)
	{
		valid = ValidateYearInteger(y1, ymd_yStart, "start year", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateMonthInteger(m1, ymd_mStart, "start month", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateDayInteger(ymd_yStart, ymd_mStart, d1, ymd_dStart, "start day", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateYearInteger(y2, ymd_yEnd, "end year", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateMonthInteger(m2, ymd_mEnd, "end month", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateDayInteger(ymd_yEnd, ymd_mEnd, d2, ymd_dEnd, "end day", true, errorMsg);
	}

	if (valid)
	{
		valid = ValidateDate1beforeDate2(ymd_yStart, ymd_mStart, ymd_dStart, ymd_yEnd, ymd_mEnd, ymd_dEnd, errorMsg);
	}

	return valid;

}
