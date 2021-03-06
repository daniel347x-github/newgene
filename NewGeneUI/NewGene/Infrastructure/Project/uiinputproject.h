#ifndef UIINPUTPROJECT_H
#define UIINPUTPROJECT_H

#include "uiproject.h"
#include "../Settings/uiinputprojectsettings.h"
#include "../../../../NewGeneBackEnd/Settings/InputModelSettings.h"
#include "uiinputmodel.h"
#include "../Settings/uiinputmodelsettings.h"
#include "inputprojectworkqueue.h"

class QListView;

class UIInputProject : public QObject, public UIProject<InputProject, UIInputProjectSettings, UIInputModelSettings, UIInputModel, UI_INPUT_PROJECT>
{

		Q_OBJECT

	public:
		UIInputProject(std::shared_ptr<UIInputProjectSettings> const & project_settings,
					   std::shared_ptr<UIInputModelSettings> const & model_settings,
					   std::shared_ptr<UIInputModel> const & model,
					   QObject * mainWindowObject_,
					   QObject * parent,
					   UIMessagerInputProject & messager_)
			: QObject(parent)
			, UIProject(project_settings, model_settings, model, parent, messager_)
			, mainWindowObject(mainWindowObject_)
			, messager(messager_)
		{
			messager.set(this);
			is_input_project = true;
		}

		void UpdateConnections();
		void DoRefreshAllWidgets();
		void PassChangeMessageToWidget(NewGeneWidget * widget, DataChangeMessage const & change_message);

	signals:
		void RefreshAllWidgets();

	public slots:
		void DataChangeMessageSlot(WidgetChangeMessages);
		void SignalMessageBox(STD_STRING);
		bool QuestionMessageBox(STD_STRING, STD_STRING); // title, question text
		void PauseLists();
		void UnpauseList(QListView*);

	public:

		QObject * mainWindowObject;
		UIMessagerInputProject & messager;

		bool is_model_equivalent(UIMessager & messager, UIInputModel * model);

	protected:

		WorkQueueManager<UI_INPUT_PROJECT> * InstantiateWorkQueue(void * ui_object, bool = false)
		{
			InputProjectWorkQueue * work_queue = new InputProjectWorkQueue();
			work_queue->SetUIObject(reinterpret_cast<UIInputProject *>(ui_object));
			work_queue->SetConnections();
			return work_queue;
		}

};

#endif // UIINPUTPROJECT_H
