#ifndef KADCOUNT_H
#define KADCOUNT_H

#include "../../../globals.h"
#include "../Table.h"

class Table_KAD_COUNT : public Table<TABLE__KAD_COUNT, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__VECTOR_PLUS_INT>
{

public:

	static std::string const KAD_COUNT__DMU_CATEGORY_STRING_CODE;
	static std::string const KAD_COUNT__COUNT;

	enum COLUMN_INDEX
	{
		  INDEX__KAD_COUNT__DMU_CATEGORY_STRING_CODE = 0
		, INDEX__KAD_COUNT__COUNT
	};

public:

	Table_KAD_COUNT()
		: Table<TABLE__KAD_COUNT, TABLE_INSTANCE_IDENTIFIER_CONTAINER_TYPE__VECTOR_PLUS_INT>()
	{

	}

	void Load(sqlite3 * db, OutputModel * output_model_, InputModel * input_model_);
	bool Update(sqlite3 * db, OutputModel & output_model_, InputModel & input_model_, DataChangeMessage & change_message);

};

#endif
