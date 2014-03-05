#ifndef VARIABLEGROUP_H
#define VARIABLEGROUP_H

#include "../Table.h"
#ifndef Q_MOC_RUN
#	include <boost/algorithm/string.hpp>
#endif

class Table_VG_CATEGORY : public Table<TABLE__VG_CATEGORY, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__VECTOR>
{

	public:

		static std::string const VG_CATEGORY_UUID;
		static std::string const VG_CATEGORY_STRING_CODE;
		static std::string const VG_CATEGORY_STRING_LONGHAND;
		static std::string const VG_CATEGORY_NOTES1;
		static std::string const VG_CATEGORY_NOTES2;
		static std::string const VG_CATEGORY_NOTES3;
		static std::string const VG_CATEGORY_FK_UOA_CATEGORY_UUID;
		static std::string const VG_CATEGORY_FLAGS;

		enum COLUMN_INDEX
		{
			  INDEX__VG_CATEGORY_UUID = 0
			, INDEX__VG_CATEGORY_STRING_CODE
			, INDEX__VG_CATEGORY_STRING_LONGHAND
			, INDEX__VG_CATEGORY_NOTES1
			, INDEX__VG_CATEGORY_NOTES2
			, INDEX__VG_CATEGORY_NOTES3
			, INDEX__VG_CATEGORY_FK_UOA_CATEGORY_UUID
			, INDEX__VG_CATEGORY_FLAGS
		};

	public:

		Table_VG_CATEGORY()
			: Table<TABLE__VG_CATEGORY, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__VECTOR>(Table_basemost::TABLE_MODEL_TYPE__INPUT_MODEL)
		{

		}

		void Load(sqlite3 * db, InputModel * input_model_);

		// For a given UOA, retrieve its VGs
		WidgetInstanceIdentifiers RetrieveVGsFromUOA(sqlite3 * db, InputModel * input_model_, UUID const & uuid);

		bool Exists(sqlite3 * db, InputModel & input_model_, WidgetInstanceIdentifier const & vg, bool const also_confirm_using_cache = true);
		bool ExistsByUuid(sqlite3 * db, InputModel & input_model_, std::string const & vg_uuid, bool const also_confirm_using_cache = true);
		bool ExistsByCode(sqlite3 * db, InputModel & input_model_, std::string const & vg_code, bool const also_confirm_using_cache = true);

		bool CreateNewVG(sqlite3 * db, InputModel & input_model, std::string const & vg_code, std::string const & vg_description, WidgetInstanceIdentifier const & uoa_to_use);
		bool DeleteVG(sqlite3 * db, InputModel * input_model_, WidgetInstanceIdentifier const & vg, DataChangeMessage & change_message);

		static std::string GetVgDisplayText(WidgetInstanceIdentifier const & vg);

};

class Table_VG_SET_MEMBER : public Table<TABLE__VG_SET_MEMBER, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__MAP>
{

	public:

		static std::string const VG_SET_MEMBER_UUID;
		static std::string const VG_SET_MEMBER_STRING_CODE;
		static std::string const VG_SET_MEMBER_STRING_LONGHAND;
		static std::string const VG_SET_MEMBER_SEQUENCE_NUMBER;
		static std::string const VG_SET_MEMBER_NOTES1;
		static std::string const VG_SET_MEMBER_NOTES2;
		static std::string const VG_SET_MEMBER_NOTES3;
		static std::string const VG_SET_MEMBER_FK_VG_CATEGORY_UUID;
		static std::string const VG_SET_MEMBER_FLAGS;

		enum COLUMN_INDEX
		{
			  INDEX__VG_SET_MEMBER_UUID = 0
			, INDEX__VG_SET_MEMBER_STRING_CODE
			, INDEX__VG_SET_MEMBER_STRING_LONGHAND
			, INDEX__VG_SET_MEMBER_SEQUENCE_NUMBER
			, INDEX__VG_SET_MEMBER_NOTES1
			, INDEX__VG_SET_MEMBER_NOTES2
			, INDEX__VG_SET_MEMBER_NOTES3
			, INDEX__VG_SET_MEMBER_FK_VG_CATEGORY_UUID
			, INDEX__VG_SET_MEMBER_FLAGS
		};

	public:

		Table_VG_SET_MEMBER()
			: Table<TABLE__VG_SET_MEMBER, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__MAP>(Table_basemost::TABLE_MODEL_TYPE__INPUT_MODEL)
		{

		}

		void Load(sqlite3 * db, InputModel * input_model_ = nullptr);
		bool DeleteVG(sqlite3 * db, InputModel * input_model_, WidgetInstanceIdentifier const & vg);

};

#endif
