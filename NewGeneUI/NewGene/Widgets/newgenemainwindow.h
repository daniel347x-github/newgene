#ifndef NEWGENEMAINWINDOW_H
#define NEWGENEMAINWINDOW_H

#include "globals.h"
#include <QMainWindow>
#include <QProgressBar>
#include <QStatusBar>
#include "newgenewidget.h"

#include <memory>
#include <map>

namespace Ui
{
	class NewGeneMainWindow;
}

class NewGeneMainWindow : public QMainWindow, public NewGeneWidget // do not reorder base classes; QWidget instance must be instantiated first
{
		Q_OBJECT

	public:
		explicit NewGeneMainWindow( QWidget * parent = 0 );
		~NewGeneMainWindow();

	signals:
		void SignalOpenOutputDataset(STD_STRING, QObject * mainWindowObject);
		void SignalCloseCurrentOutputDataset();
		void SignalOpenInputDataset(STD_STRING, QObject * mainWindowObject);
		void SignalCloseCurrentInputDataset();

	public slots:
		void doInitialize();
		void SignalMessageBox(STD_STRING);
		void ReceiveSignalStartProgressBar(int, STD_INT64 const, STD_INT64 const);
		void ReceiveSignalStopProgressBar(int);
		void ReceiveSignalUpdateProgressBarValue(int, STD_INT64 const);
		void ReceiveSignalUpdateStatusBarText(int, STD_STRING const);

	protected:
		void changeEvent( QEvent * e );

	private slots:
		void on_actionClose_Current_Input_Dataset_triggered();
		void on_actionOpen_Input_Dataset_triggered();
		void on_actionOpen_Output_Dataset_triggered();
		void on_actionClose_Current_Output_Dataset_triggered();

	private:
		Ui::NewGeneMainWindow * ui;

		friend class NewGeneWidget;

		std::map<int, std::unique_ptr<QProgressBar>> status_bar_progress_bars;
		std::map<int, std::unique_ptr<QProgressBar>> main_pane_progress_bars;

};

#endif // NEWGENEMAINWINDOW_H
