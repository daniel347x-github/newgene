#include "Fields.h"

std::int64_t const & BaseField::GetInt64Ref() const
{

	if (!IsFieldTypeInt64(field_type))
	{
		boost::format msg("Field data type is not convertible to int64.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_INT64:
			{
				Field<FIELD_TYPE_INT64> const & myself = static_cast<Field<FIELD_TYPE_INT64> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_UINT64:
			{
				Field<FIELD_TYPE_UINT64> const & myself = static_cast<Field<FIELD_TYPE_UINT64> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_TIMESTAMP:
			{
				Field<FIELD_TYPE_TIMESTAMP> const & myself = static_cast<Field<FIELD_TYPE_TIMESTAMP> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	static std::int64_t dummy = 0;
	return dummy;

}

std::int32_t const & BaseField::GetInt32Ref() const
{

	if (!IsFieldTypeInt32(field_type))
	{
		boost::format msg("Field data type is not convertible to int32.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_INT32:
			{
				Field<FIELD_TYPE_INT32> const & myself = static_cast<Field<FIELD_TYPE_INT32> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_UINT32:
			{
				Field<FIELD_TYPE_UINT32> const & myself = static_cast<Field<FIELD_TYPE_UINT32> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	static std::int32_t dummy = 0;
	return dummy;

}

std::string const & BaseField::GetStringRef() const
{

	if (!IsFieldTypeString(field_type))
	{
		boost::format msg("Field data type is not convertible to a string.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_STRING_FIXED:
			{
				Field<FIELD_TYPE_STRING_FIXED> const & myself = static_cast<Field<FIELD_TYPE_STRING_FIXED> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_VAR:
			{
				Field<FIELD_TYPE_STRING_VAR> const & myself = static_cast<Field<FIELD_TYPE_STRING_VAR> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_UUID:
			{
				Field<FIELD_TYPE_UUID> const & myself = static_cast<Field<FIELD_TYPE_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_UUID_FOREIGN:
			{
				Field<FIELD_TYPE_UUID_FOREIGN> const & myself = static_cast<Field<FIELD_TYPE_UUID_FOREIGN> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_CODE:
			{
				Field<FIELD_TYPE_STRING_CODE> const & myself = static_cast<Field<FIELD_TYPE_STRING_CODE> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_LONGHAND:
			{
				Field<FIELD_TYPE_STRING_LONGHAND> const & myself = static_cast<Field<FIELD_TYPE_STRING_LONGHAND> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_1:
			{
				Field<FIELD_TYPE_NOTES_1> const & myself = static_cast<Field<FIELD_TYPE_NOTES_1> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_2:
			{
				Field<FIELD_TYPE_NOTES_2> const & myself = static_cast<Field<FIELD_TYPE_NOTES_2> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_3:
			{
				Field<FIELD_TYPE_NOTES_3> const & myself = static_cast<Field<FIELD_TYPE_NOTES_3> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID_STRING:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID_STRING> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID_STRING> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_CODE:
			{
				Field<FIELD_TYPE_DMU_MEMBER_CODE> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_CODE> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_DESCRIPTION:
			{
				Field<FIELD_TYPE_DMU_MEMBER_DESCRIPTION> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_DESCRIPTION> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID:
			{
				Field<FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID> const & myself = static_cast<Field<FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	static std::string dummy;
	return dummy;

}

std::int64_t BaseField::GetInt64() const
{

	if (!IsFieldTypeInt64(field_type))
	{
		boost::format msg("Field data type is not convertible to int64.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_INT64:
			{
				Field<FIELD_TYPE_INT64> const & myself = static_cast<Field<FIELD_TYPE_INT64> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_UINT64:
			{
				Field<FIELD_TYPE_UINT64> const & myself = static_cast<Field<FIELD_TYPE_UINT64> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_TIMESTAMP:
			{
				Field<FIELD_TYPE_TIMESTAMP> const & myself = static_cast<Field<FIELD_TYPE_TIMESTAMP> const &>(*this);
				return static_cast<std::int64_t const &>(myself.GetValueReference());
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	return 0;

}

std::int32_t BaseField::GetInt32() const
{
	if (!IsFieldTypeInt32(field_type))
	{
		boost::format msg("Field data type is not convertible to int32.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_INT32:
			{
				Field<FIELD_TYPE_INT32> const & myself = static_cast<Field<FIELD_TYPE_INT32> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_UINT32:
			{
				Field<FIELD_TYPE_UINT32> const & myself = static_cast<Field<FIELD_TYPE_UINT32> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID_NUMERIC> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_DAY:
			{
				Field<FIELD_TYPE_DAY> const & myself = static_cast<Field<FIELD_TYPE_DAY> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_MONTH:
			{
				Field<FIELD_TYPE_MONTH> const & myself = static_cast<Field<FIELD_TYPE_MONTH> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		case FIELD_TYPE_YEAR:
			{
				Field<FIELD_TYPE_YEAR> const & myself = static_cast<Field<FIELD_TYPE_YEAR> const &>(*this);
				return static_cast<std::int32_t const &>(myself.GetValueReference());
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	return 0;

}

double BaseField::GetDouble() const
{

	if (!IsFieldTypeFloat(field_type))
	{
		boost::format msg("Field data type is not convertible to double.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_FLOAT:
			{
				Field<FIELD_TYPE_FLOAT> const & myself = static_cast<Field<FIELD_TYPE_FLOAT> const &>(*this);
				return static_cast<double const &>(myself.GetValueReference());
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	return 0.0;

}

std::string BaseField::GetString() const
{

	if (!IsFieldTypeString(field_type))
	{
		boost::format msg("Field data type is not convertible to a string.");
		throw NewGeneException() << newgene_error_description(msg.str());
	}

	switch (field_type)
	{

		case FIELD_TYPE_STRING_FIXED:
			{
				Field<FIELD_TYPE_STRING_FIXED> const & myself = static_cast<Field<FIELD_TYPE_STRING_FIXED> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_VAR:
			{
				Field<FIELD_TYPE_STRING_VAR> const & myself = static_cast<Field<FIELD_TYPE_STRING_VAR> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_UUID:
			{
				Field<FIELD_TYPE_UUID> const & myself = static_cast<Field<FIELD_TYPE_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_UUID_FOREIGN:
			{
				Field<FIELD_TYPE_UUID_FOREIGN> const & myself = static_cast<Field<FIELD_TYPE_UUID_FOREIGN> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_CODE:
			{
				Field<FIELD_TYPE_STRING_CODE> const & myself = static_cast<Field<FIELD_TYPE_STRING_CODE> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_STRING_LONGHAND:
			{
				Field<FIELD_TYPE_STRING_LONGHAND> const & myself = static_cast<Field<FIELD_TYPE_STRING_LONGHAND> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_1:
			{
				Field<FIELD_TYPE_NOTES_1> const & myself = static_cast<Field<FIELD_TYPE_NOTES_1> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_2:
			{
				Field<FIELD_TYPE_NOTES_2> const & myself = static_cast<Field<FIELD_TYPE_NOTES_2> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_NOTES_3:
			{
				Field<FIELD_TYPE_NOTES_3> const & myself = static_cast<Field<FIELD_TYPE_NOTES_3> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_UUID_STRING:
			{
				Field<FIELD_TYPE_DMU_MEMBER_UUID_STRING> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_UUID_STRING> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_CODE:
			{
				Field<FIELD_TYPE_DMU_MEMBER_CODE> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_CODE> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_DMU_MEMBER_DESCRIPTION:
			{
				Field<FIELD_TYPE_DMU_MEMBER_DESCRIPTION> const & myself = static_cast<Field<FIELD_TYPE_DMU_MEMBER_DESCRIPTION> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		case FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID:
			{
				Field<FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID> const & myself = static_cast<Field<FIELD_TYPE_FK_TO_DMU_CATEGORY_UUID> const &>(*this);
				return myself.GetValueReference();
			}
			break;

		default:
			{
				boost::format msg("Unknown field data type.");
				throw NewGeneException() << newgene_error_description(msg.str());
			}
			break;

	}

	return std::string();

}
