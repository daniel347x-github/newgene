#ifndef UILOGGINGMANAGER_H
#define UILOGGINGMANAGER_H

#include "uimanager.h"
#ifndef Q_MOC_RUN
#	include <boost/filesystem.hpp>
#endif

class NewGeneMainWindow;

class UILoggingManager : public UIManager
{
		Q_OBJECT
	public:
		explicit UILoggingManager( QObject * parent = 0 );

		static UILoggingManager & getLoggingManager();

	signals:

	public slots:

	protected:

		bool ObtainLogfilePath();

	private:

		static std::unique_ptr<UILoggingManager> _loggingManager;

		boost::filesystem::path loggingPath;

};

#endif // UILOGGINGMANAGER_H
