#ifndef UISETTINGSMANAGER_H
#define UISETTINGSMANAGER_H

#include "globals.h"
#include "uimanager.h"
#include "..\..\..\NewGeneBackEnd\Settings\SettingsManager.h"
#include <QString>
#ifndef Q_MOC_RUN
#   include <boost\filesystem.hpp>
#   include <boost/property_tree/ptree.hpp>
#   include <boost/property_tree/xml_parser.hpp>
#endif
#include "../../../NewGeneBackEnd/Settings/Setting.h"

class NewGeneMainWindow;
class UIAllProjectSettings;
class UIAllGlobalSettings;

class UISettingsManager : public QObject, public UIManager<UISettingsManager, SettingsManager, MANAGER_DESCRIPTION_NAMESPACE::MANAGER_SETTINGS_UI, MANAGER_DESCRIPTION_NAMESPACE::MANAGER_SETTINGS>
{

		Q_OBJECT

	public:

		explicit UISettingsManager( QObject * parent = 0 );

		Setting const & get_global_setting();

		bool ObtainGlobalSettingsPath();
		boost::filesystem::path getGlobalSettingsPath() { return global_settings_path; }

	signals:

	public slots:

	protected:


	private:

		boost::filesystem::path global_settings_path;
		std::unique_ptr<UIAllGlobalSettings> _global_settings;

};

#endif // UISETTINGSMANAGER_H
