#ifndef NEWGENEWIDGET_H
#define NEWGENEWIDGET_H

#include "globals.h"

class QWidget;
class NewGeneMainWindow;

class NewGeneWidget
{
	public:
		explicit NewGeneWidget( QWidget * self_ = 0 );

		NewGeneMainWindow & mainWindow();

		virtual void PrepareInputWidget();
		virtual void PrepareOutputWidget();

	protected:

		virtual void UpdateInputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE connection_type, UIInputProject * project);
		virtual void UpdateOutputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE connection_type, UIOutputProject * project);

	private:

		QWidget * self;
		UIInputProject * inp;
		UIOutputProject * outp;

	public:

		static NewGeneMainWindow * theMainWindow;

};

#endif // NEWGENEWIDGET_H
