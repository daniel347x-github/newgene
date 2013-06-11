#ifndef UIPROJECTINPUTSETTINGS_H
#define UIPROJECTINPUTSETTINGS_H

#include "../../../NewGeneBackEnd/Settings/InputProjectSettings.h"
#include "../../../NewGeneBackEnd/Settings/Setting.h"
#include "../../../NewGeneBackEnd/Project/InputProject.h"
#include "uiallprojectsettings.h"
#include "Base/UISetting.h"

namespace INPUT_PROJECT_SETTINGS_UI_NAMESPACE
{

	enum INPUT_PROJECT_SETTINGS_UI
	{
		  SETTING_FIRST = 0
		, SETTING_LAST
	};

}

class UIInputProjectSettings : public UIAllProjectSettings<InputProjectSettings, INPUT_PROJECT_SETTINGS_BACKEND_NAMESPACE::INPUT_PROJECT_SETTINGS_BACKEND, INPUT_PROJECT_SETTINGS_UI_NAMESPACE::INPUT_PROJECT_SETTINGS_UI, BackendProjectInputSetting, UIProjectInputSetting>
{

		Q_OBJECT

	signals:

	public slots:


	public:
		UIInputProjectSettings(UIMessager & messager, boost::filesystem::path const path_to_settings = boost::filesystem::path(), QObject * parent = NULL)
			: UIAllProjectSettings(messager, path_to_settings, parent)
		{

		}

		void SetMapEntry(Messager & messager_, SettingInfo & setting_info, boost::property_tree::ptree & pt);
		UIProjectInputSetting * CloneSetting(Messager & messager_, UIProjectInputSetting * current_setting, SettingInfo & setting_info) const;
		UIProjectInputSetting * NewSetting(Messager & messager_, SettingInfo & setting_info, void const * setting_value_void = NULL);
		void SetPTreeEntry(Messager & messager, INPUT_PROJECT_SETTINGS_UI_NAMESPACE::INPUT_PROJECT_SETTINGS_UI which_setting, boost::property_tree::ptree & pt);

		virtual void WriteSettingsToFile(Messager & messager)
		{
			boost::property_tree::ptree pt;
			UIOnlySettings & uisettings = getUISettings();
			InputProjectSettings & backendsettings = getBackendSettings();
			uisettings.WriteSettingsToPtree(messager, pt);
			backendsettings.WriteSettingsToPtree(messager, pt);
			uisettings.WritePtreeToFile(messager, pt);
		}

};

#endif // UIPROJECTINPUTSETTINGS_H
