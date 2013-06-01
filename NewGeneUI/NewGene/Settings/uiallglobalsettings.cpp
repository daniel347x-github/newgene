#include "uiallglobalsettings.h"
#include "uiallglobalsettings_list.h"
#include "globals.h"

#define GET_GLOBAL_UI_SETTING_INFO(GLOBAL_UI_SETTING_ENUM, SETTING_INFO_ENUM, SETTING_STRING, SETTING_DEFAULT) \
case GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_UI_SETTING_ENUM: \
	{ \
		return SettingInfo(SettingInfo::SETTING_INFO_ENUM, \
						   static_cast<int>(GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_UI_SETTING_ENUM), \
						   SETTING_STRING, \
						   SETTING_DEFAULT); \
	} \
	break; \


#define GLOBAL_UI_SET_MAP_ENTRY__STRING(SETTING_INFO_ENUM, SETTING_CLASS) \
	case SettingInfo::SETTING_INFO_ENUM: \
		{ \
			std::string string_setting = pt.get<std::string>(setting_info.text, setting_info.default_val_string); \
			_settings_map[static_cast<GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_SETTINGS_UI>(setting_info.enum_index)] = std::unique_ptr<UIGlobalSetting>(SettingFactory<SETTING_CLASS>()(messager, string_setting)); \
		} \
		break; \


#define GLOBAL_UI_CLONE_SETTING__STRING(SETTING_INFO_ENUM, SETTING_CLASS) \
	case SettingInfo::SETTING_INFO_ENUM: \
		{ \
			SETTING_CLASS * setting = dynamic_cast<SETTING_CLASS*>(current_setting); \
			return new SETTING_CLASS(messager, setting->getString()); \
		} \
		break; \


#define GLOBAL_UI_NEW_SETTING__STRING(SETTING_INFO_ENUM, SETTING_CLASS) \
	case SettingInfo::SETTING_INFO_ENUM: \
		{ \
			std::string string_setting = setting_info.default_val_string; \
			if (setting_value_void) \
			{ \
				string_setting = *((std::string *)(setting_value_void)); \
			} \
			return new SETTING_CLASS(messager, string_setting); \
		} \
		break; \


SettingInfo UIGlobalSetting::GetSettingInfoFromEnum(Messager & messager_, int const value__)
{

	UIMessager & messager = static_cast<UIMessager &>(messager_);

	GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_SETTINGS_UI const value_ = static_cast<GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_SETTINGS_UI const>(value__);

	switch (value_)
	{

		GET_GLOBAL_UI_SETTING_INFO(MRU_INPUT_PROJECTS_LIST, SETTING_CLASS_UI_GLOBAL_SETTING__MRU_INPUT_PROJECTS_LIST, "MRU_INPUT_PROJECTS_LIST", "")
		GET_GLOBAL_UI_SETTING_INFO(MRU_OUTPUT_PROJECTS_LIST, SETTING_CLASS_UI_GLOBAL_SETTING__MRU_OUTPUT_PROJECTS_LIST, "MRU_OUTPUT_PROJECTS_LIST", "")
		GET_GLOBAL_UI_SETTING_INFO(OPEN_INPUT_PROJECTS_LIST, SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_INPUT_PROJECTS_LIST, "OPEN_INPUT_PROJECTS_LIST", "L:\\daniel347x\\__DanExtras\\NewGene\\Projects\\Input\\TestInputProjectSettings.xml;L:\\daniel347x\\__DanExtras\\NewGene\\Projects\\Input\\TestInputProjectModel.xml")
		GET_GLOBAL_UI_SETTING_INFO(OPEN_OUTPUT_PROJECTS_LIST, SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_OUTPUT_PROJECTS_LIST, "OPEN_OUTPUT_PROJECTS_LIST", "L:\\daniel347x\\__DanExtras\\NewGene\\Projects\\Output\\TestOutputProjectSettings.xml;L:\\daniel347x\\__DanExtras\\NewGene\\Projects\\Output\\TestOutputProjectModel.xml")

		default:
			{
				boost::format msg("Settings information is not available for GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_SETTINGS_UI value %1%.  Using empty setting.");
				msg % value_;
				messager.AppendMessage(new MessagerWarningMessage(MESSAGER_MESSAGE__INVALID_SETTING_ENUM_VALUE, msg.str()));
			}

	}

	return SettingInfo();

}

void UIAllGlobalSettings::UIOnlySettings::SetMapEntry(Messager & messager_, SettingInfo & setting_info, boost::property_tree::ptree & pt)
{

	UIMessager & messager = static_cast<UIMessager &>(messager_);

	switch (setting_info.setting_class)
	{

		GLOBAL_UI_SET_MAP_ENTRY__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_INPUT_PROJECTS_LIST>)
		GLOBAL_UI_SET_MAP_ENTRY__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_OUTPUT_PROJECTS_LIST>)
		GLOBAL_UI_SET_MAP_ENTRY__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_INPUT_PROJECTS_LIST>)
		GLOBAL_UI_SET_MAP_ENTRY__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_OUTPUT_PROJECTS_LIST>)

		default:
			{
				boost::format msg("Unknown UI global setting \"%1%\" (\"%2%\") being loaded.");
				msg % setting_info.text % setting_info.setting_class;
				messager.AppendMessage(new MessagerWarningMessage(MESSAGER_MESSAGE__INVALID_SETTING_INFO_OBJECT, msg.str()));
			}
			break;

	}

}

UIGlobalSetting * UIAllGlobalSettings::UIOnlySettings::CloneSetting(Messager & messager_, UIGlobalSetting * current_setting, SettingInfo & setting_info) const
{

	UIMessager & messager = static_cast<UIMessager &>(messager_);

	try
	{

		switch (setting_info.setting_class)
		{

			GLOBAL_UI_CLONE_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_INPUT_PROJECTS_LIST>)
			GLOBAL_UI_CLONE_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_OUTPUT_PROJECTS_LIST>)
			GLOBAL_UI_CLONE_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_INPUT_PROJECTS_LIST>)
			GLOBAL_UI_CLONE_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_OUTPUT_PROJECTS_LIST>)

			default:
				{
					boost::format msg("Unknown UI global setting \"%1%\" (\"%2%\") being requested.");
					msg % setting_info.text % setting_info.setting_class;
					messager.AppendMessage(new MessagerWarningMessage(MESSAGER_MESSAGE__INVALID_SETTING_INFO_OBJECT, msg.str()));
				}
				break;

		}

	}
	catch (std::bad_cast & e)
	{
		boost::format msg("Unable to retrieve setting \"%1%\" (\"%2%\"): %3%.");
		msg % setting_info.text % setting_info.setting_class % e.what();
		messager.AppendMessage(new MessagerWarningMessage(MESSAGER_MESSAGE__INVALID_SETTING_INFO_OBJECT, msg.str()));
	}

	return NULL;

}

UIGlobalSetting * UIAllGlobalSettings::UIOnlySettings::NewSetting(Messager & messager_, SettingInfo & setting_info, void const * setting_value_void)
{

	UIMessager & messager = static_cast<UIMessager &>(messager_);

	switch (setting_info.setting_class)
	{

		GLOBAL_UI_NEW_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_INPUT_PROJECTS_LIST>)
		GLOBAL_UI_NEW_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__MRU_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::MRU_OUTPUT_PROJECTS_LIST>)
		GLOBAL_UI_NEW_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_INPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_INPUT_PROJECTS_LIST>)
		GLOBAL_UI_NEW_SETTING__STRING(SETTING_CLASS_UI_GLOBAL_SETTING__OPEN_OUTPUT_PROJECTS_LIST, UIGlobalSetting_Projects_Files_List<GLOBAL_SETTINGS_UI_NAMESPACE::OPEN_OUTPUT_PROJECTS_LIST>)

		default:
			{
				boost::format msg("Unknown UI global setting \"%1%\" (\"%2%\") being updated.");
				msg % setting_info.text % setting_info.setting_class;
				messager.AppendMessage(new MessagerWarningMessage(MESSAGER_MESSAGE__INVALID_SETTING_INFO_OBJECT, msg.str()));
			}
			break;

	}

	return NULL;

}

UIAllGlobalSettings::UIOnlySettings & UIAllGlobalSettings::getUISettings()
{
	if (!__impl)
	{
		boost::format msg( "Internal settings implementation not yet constructed." );
		throw NewGeneException() << newgene_error_description( msg.str() );
	}
	return static_cast<UIAllGlobalSettings::UIOnlySettings &>(getUISettings_base<GlobalSettings, UIOnlySettings, GLOBAL_SETTINGS_UI_NAMESPACE::GLOBAL_SETTINGS_UI, UIGlobalSetting>(*__impl));
}

GlobalSettings & UIAllGlobalSettings::getBackendSettings()
{
	if (!__impl)
	{
		boost::format msg( "Internal settings implementation not yet constructed." );
		throw NewGeneException() << newgene_error_description( msg.str() );
	}
	return static_cast<GlobalSettings &>(getBackendSettings_base<GlobalSettings, UIOnlySettings, GLOBAL_SETTINGS_BACKEND_NAMESPACE::GLOBAL_SETTINGS_BACKEND, BackendGlobalSetting>(*__impl));
}

UIAllGlobalSettings::UIAllGlobalSettings(UIMessager & messager, boost::filesystem::path const path_to_settings, QObject * parent) :
	UIAllSettings(messager, parent)
{
	CreateImplementation(messager, path_to_settings);
}

void UIAllGlobalSettings::_impl::CreateInternalImplementations(UIMessager & messager, boost::filesystem::path const path_to_settings)
{
	__ui_impl.reset(new _UIRelatedImpl(messager, path_to_settings));
	__backend_impl.reset(new _BackendRelatedImpl(messager, path_to_settings));
}

void UIAllGlobalSettings::CreateImplementation(UIMessager & messager, boost::filesystem::path const path_to_settings)
{
	__impl.reset(new _impl(messager, path_to_settings));
}
