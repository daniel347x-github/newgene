#include "inputmodelworkqueue.h"
#include "uiinputmodel.h"
#include "globals.h"
#include "uiprojectmanager.h"
#include "uimessagersingleshot.h"

InputModelWorkQueue::InputModelWorkQueue(bool isPool2_, QObject * parent)
	: WorkQueueManager<UI_INPUT_MODEL>(isPool2_, parent)
	, inp(nullptr)
{
}

UIInputModel * InputModelWorkQueue::get()
{
	return reinterpret_cast<UIInputModel*>(inp);
}

void InputModelWorkQueue::TestSlot()
{
	emit SignalMessageBox("Input model's \"TestSlot()\" successfully called and handled.");
}

void InputModelWorkQueue::SetConnections()
{
	connect(this, SIGNAL(SignalMessageBox(STD_STRING)), get(), SLOT(SignalMessageBox(STD_STRING)));
	connect(&projectManagerUI(), SIGNAL(LoadFromDatabase(UI_INPUT_MODEL_PTR)), this, SLOT(LoadFromDatabase(UI_INPUT_MODEL_PTR)));
}

void InputModelWorkQueue::LoadFromDatabase(UI_INPUT_MODEL_PTR model)
{
	emit SignalMessageBox("Input model's \"LoadFromDatabase()\" successfully called and handled.");
	UIMessagerSingleShot messager;
	if (!get()->is_model_equivalent(messager.get(), model))
	{
		return;
	}

	// Lock model and load all from database here
	{

		get()->loaded(true);
	}

	// emit signal to trigger loading of output model here
}

