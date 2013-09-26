#ifndef ACTIONWIDGETS_H
#define ACTIONWIDGETS_H

#include "../Utilities/WidgetIdentifier.h"

enum WIDGET_ACTIONS
{

	  WIDGET_ACTIONS_FIRST = 0
	, ACTION_TYPE_NONE = WIDGET_ACTIONS_FIRST

	, ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED
	, ACTION_KAD_COUNT_CHANGE
	, ACTION_DO_RANDOM_SAMPLING_CHANGE
	, ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE
	, ACTION_DATETIME_RANGE_CHANGE
	, ACTION_GENERATE_OUTPUT

	, WIDGET_ACTIONS_LAST

};

enum WIDGET_ACTION_ITEM_REQUEST_REASON
{

	  WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN

	, WIDGET_ACTION_ITEM_REQUEST_REASON__ADD_ITEMS
	, WIDGET_ACTION_ITEM_REQUEST_REASON__REMOVE_ITEMS
	, WIDGET_ACTION_ITEM_REQUEST_REASON__UPDATE_ITEMS
	, WIDGET_ACTION_ITEM_REQUEST_REASON__DO_ACTION // for actions not associated with an item

	, WIDGET_ACTION_ITEM_REQUEST_REASON__REFRESH_ALL_WIDGETS

};

class WidgetActionItem
{

	public:

		WidgetActionItem()
		{

		}

		virtual ~WidgetActionItem()
		{

		}

		WidgetActionItem(WidgetActionItem const & rhs)
		{

		}

};

typedef std::shared_ptr<WidgetActionItem> WidgetActionItemSharedPtr;
typedef std::pair<WidgetInstanceIdentifier, WidgetActionItemSharedPtr> InstanceActionItem;
typedef std::vector<InstanceActionItem> InstanceActionItems;


class WidgetActionItem__Checkbox : public WidgetActionItem
{

	public:

		WidgetActionItem__Checkbox(bool const checked_)
			: WidgetActionItem()
			, checked(checked_)
		{

		}

		WidgetActionItem__Checkbox(WidgetActionItem__Checkbox const & rhs)
			: WidgetActionItem(rhs)
			, checked(rhs.checked)
		{

		}

		~WidgetActionItem__Checkbox()
		{

		}

		void setChecked(bool const checked_)
		{
			checked = checked_;
		}

		bool isChecked() const
		{
			return checked;
		}

	protected:

		bool checked;

};

class WidgetActionItem__Spinbox : public WidgetActionItem
{

	public:

		WidgetActionItem__Spinbox(int const value__)
			: WidgetActionItem()
			, value_(value__)
		{

		}

		WidgetActionItem__Spinbox(WidgetActionItem__Spinbox const & rhs)
			: WidgetActionItem(rhs)
			, value_(rhs.value_)
		{

		}

		~WidgetActionItem__Spinbox()
		{

		}

		void setValue(int const value__)
		{
			value_ = value__;
		}

		int getValue() const
		{
			return value_;
		}

	protected:

		int value_;

};

class WidgetActionItem__Int64 : public WidgetActionItem
{

	public:

		WidgetActionItem__Int64(std::int64_t const value__)
			: WidgetActionItem()
			, value_(value__)
		{

		}

		WidgetActionItem__Int64(WidgetActionItem__Int64 const & rhs)
			: WidgetActionItem(rhs)
			, value_(rhs.value_)
		{

		}

		~WidgetActionItem__Int64()
		{

		}

		void setValue(std::int64_t const value__)
		{
			value_ = value__;
		}

		std::int64_t getValue() const
		{
			return value_;
		}

	protected:

		std::int64_t value_;

};

class WidgetActionItem__DateTime : public WidgetActionItem
{

	public:

		WidgetActionItem__DateTime(std::int64_t const value__)
			: WidgetActionItem()
			, value_(value__)
		{

		}

		WidgetActionItem__DateTime(WidgetActionItem__DateTime const & rhs)
			: WidgetActionItem(rhs)
			, value_(rhs.value_)
		{

		}

		~WidgetActionItem__DateTime()
		{

		}

		void setValue(std::int64_t const value__)
		{
			value_ = value__;
		}

		std::int64_t getValue() const
		{
			return value_;
		}

	protected:

		std::int64_t value_;

};

class WidgetActionItem__GenerateOutput : public WidgetActionItem
{

public:

	WidgetActionItem__GenerateOutput()
		: WidgetActionItem()
	{

	}

	WidgetActionItem__GenerateOutput(WidgetActionItem__GenerateOutput const & rhs)
		: WidgetActionItem(rhs)
	{

	}

	~WidgetActionItem__GenerateOutput()
	{

	}

};

class WidgetActionItemRequest_base
{

	public:

		WidgetActionItemRequest_base(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: reason(reason_)
			, items(std::make_shared<InstanceActionItems>(items_))
		{

		}

		WidgetActionItemRequest_base(WidgetActionItemRequest_base const & rhs)
			: reason(rhs.reason)
			, items(rhs.items)
		{

		}

		WIDGET_ACTION_ITEM_REQUEST_REASON reason;
		std::shared_ptr<InstanceActionItems> items;

};

template<WIDGET_ACTIONS WIDGET>
class WidgetActionItemRequest : public WidgetActionItemRequest_base
{

};


/************************************************************************/
// ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED> : public WidgetActionItemRequest_base
{
	public:
		WidgetActionItemRequest<ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: WidgetActionItemRequest_base(reason_, items_)
		{
		}
		WidgetActionItemRequest<ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED>(WidgetActionItemRequest<ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED> const & rhs)
			: WidgetActionItemRequest_base(rhs)
		{
		}
};
typedef WidgetActionItemRequest<ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED> WidgetActionItemRequest_ACTION_VARIABLE_GROUP_SET_MEMBER_SELECTION_CHANGED;

/************************************************************************/
// ACTION_KAD_COUNT_CHANGE
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_KAD_COUNT_CHANGE> : public WidgetActionItemRequest_base
{
	public:
		WidgetActionItemRequest<ACTION_KAD_COUNT_CHANGE>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: WidgetActionItemRequest_base(reason_, items_)
		{
		}
		WidgetActionItemRequest<ACTION_KAD_COUNT_CHANGE>(WidgetActionItemRequest<ACTION_KAD_COUNT_CHANGE> const & rhs)
			: WidgetActionItemRequest_base(rhs)
		{
		}
};
typedef WidgetActionItemRequest<ACTION_KAD_COUNT_CHANGE> WidgetActionItemRequest_ACTION_KAD_COUNT_CHANGE;

/************************************************************************/
// ACTION_DO_RANDOM_SAMPLING_CHANGE
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_DO_RANDOM_SAMPLING_CHANGE> : public WidgetActionItemRequest_base
{
	public:
		WidgetActionItemRequest<ACTION_DO_RANDOM_SAMPLING_CHANGE>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: WidgetActionItemRequest_base(reason_, items_)
		{
		}
		WidgetActionItemRequest<ACTION_DO_RANDOM_SAMPLING_CHANGE>(WidgetActionItemRequest<ACTION_DO_RANDOM_SAMPLING_CHANGE> const & rhs)
			: WidgetActionItemRequest_base(rhs)
		{
		}
};
typedef WidgetActionItemRequest<ACTION_DO_RANDOM_SAMPLING_CHANGE> WidgetActionItemRequest_ACTION_DO_RANDOM_SAMPLING_CHANGE;

/************************************************************************/
// ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE> : public WidgetActionItemRequest_base
{
	public:
		WidgetActionItemRequest<ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: WidgetActionItemRequest_base(reason_, items_)
		{
		}
		WidgetActionItemRequest<ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE>(WidgetActionItemRequest<ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE> const & rhs)
			: WidgetActionItemRequest_base(rhs)
		{
		}
};
typedef WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE> WidgetActionItemRequest_ACTION_RANDOM_SAMPLING_COUNT_PER_STAGE_CHANGE;

/************************************************************************/
// ACTION_DATETIME_RANGE_CHANGE
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE> : public WidgetActionItemRequest_base
{
	public:
		WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__UNKNOWN, InstanceActionItems items_ = InstanceActionItems())
			: WidgetActionItemRequest_base(reason_, items_)
		{
		}
		WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE>(WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE> const & rhs)
			: WidgetActionItemRequest_base(rhs)
		{
		}
};
typedef WidgetActionItemRequest<ACTION_DATETIME_RANGE_CHANGE> WidgetActionItemRequest_ACTION_DATETIME_RANGE_CHANGE;

/************************************************************************/
// ACTION_GENERATE_OUTPUT
/************************************************************************/
template<>
class WidgetActionItemRequest<ACTION_GENERATE_OUTPUT> : public WidgetActionItemRequest_base
{
public:
	WidgetActionItemRequest<ACTION_GENERATE_OUTPUT>(WIDGET_ACTION_ITEM_REQUEST_REASON const reason_ = WIDGET_ACTION_ITEM_REQUEST_REASON__DO_ACTION, InstanceActionItems items_ = InstanceActionItems())
		: WidgetActionItemRequest_base(reason_, items_)
	{
	}
	WidgetActionItemRequest<ACTION_GENERATE_OUTPUT>(WidgetActionItemRequest<ACTION_GENERATE_OUTPUT> const & rhs)
		: WidgetActionItemRequest_base(rhs)
	{
	}
};
typedef WidgetActionItemRequest<ACTION_GENERATE_OUTPUT> WidgetActionItemRequest_ACTION_GENERATE_OUTPUT;

#endif
