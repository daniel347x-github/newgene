#ifndef NEWGENEWIDGET_H
#define NEWGENEWIDGET_H

#include "globals.h"

class QWidget;
class NewGeneMainWindow;
class UISettingsManager;
class UIProjectManager;
class UILoggingManager;
class UIModelManager;
class UIDocumentManager;
class UIStatusManager;

class NewGeneWidget
{
	public:
		explicit NewGeneWidget( QWidget * self_ = 0 );

		NewGeneMainWindow & mainWindow();
		static UIProjectManager & projectManager();
		static UISettingsManager & settingsManager();
		static UILoggingManager & loggingManager();
		static UIModelManager & modelManager();
		static UIDocumentManager & documentManager();
		static UIStatusManager & statusManager();

	private:
		QWidget * self;

};

#endif // NEWGENEWIDGET_H
