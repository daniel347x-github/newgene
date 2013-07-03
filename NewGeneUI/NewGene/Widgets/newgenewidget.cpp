
#include <QWidget>
#include "newgenemainwindow.h"
#include "newgenewidget.h"
#include "uistatusmanager.h"
#include "../../../NewGeneBackEnd/Utilities/UUID.h"

NewGeneMainWindow * NewGeneWidget::theMainWindow = nullptr;

NewGeneWidget::NewGeneWidget( WidgetCreationInfo const & creation_info )
	: self( creation_info.self )
	, inp(nullptr)
	, outp(nullptr)
	, widget_type(creation_info.widget_type)
	, uuid(newUUID())
	, widget_nature(creation_info.widget_nature)
	, top_level(creation_info.top_level)
	, data_instance(creation_info.data_instance)
{
}

NewGeneWidget::~NewGeneWidget()
{
}

void NewGeneWidget::PrepareInputWidget()
{
	if (self == nullptr)
	{
		return;
	}
	self->connect(&projectManagerUI(), SIGNAL(UpdateInputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE, UIInputProject *)), self, SLOT(UpdateInputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE, UIInputProject *)));
}

void NewGeneWidget::PrepareOutputWidget()
{
	if (self == nullptr)
	{
		return;
	}
	self->connect(&projectManagerUI(), SIGNAL(UpdateOutputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE, UIOutputProject *)), self, SLOT(UpdateOutputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE, UIOutputProject *)));
}

NewGeneMainWindow & NewGeneWidget::mainWindow()
{
	return *theMainWindow; // FIX THIS!!!
}

// Be sure to call this only in the context of the UI thread
void NewGeneWidget::ShowMessageBox(std::string msg)
{
	QMessageBox msgBox;
	msgBox.setText( msg.c_str() );
	msgBox.exec();
}

void NewGeneWidget::UpdateInputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE connection_type, UIInputProject * project)
{

	if (!IsInputProjectWidget())
	{
		boost::format msg("Attempting to connect an input project to a widget that has not registered as an input widget.");
		statusManagerUI().PostStatus( msg.str().c_str(), UIStatusManager::IMPORTANCE_HIGH, true );
		return;
	}

	if (connection_type == UIProjectManager::RELEASE_CONNECTIONS_INPUT_PROJECT)
	{
		if (project && project == inp)
		{
			inp->RemoveWidgetFromUUIDMap(uuid);
			if (data_instance.uuid)
			{
				inp->RemoveWidgetDataItemFromUUIDMap(uuid, *data_instance.uuid);
			}
		}
		inp = nullptr;

		// TODO: release connections here
	}

	else if (connection_type == UIProjectManager::ESTABLISH_CONNECTIONS_INPUT_PROJECT)
	{
		inp = project;

		if (!inp)
		{
			statusManagerUI().PostStatus( "Input project is unavailable.", UIStatusManager::IMPORTANCE_HIGH, true );
			return;
		}
		try
		{
			inp->AddWidgetUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), uuid);
			if (data_instance.uuid)
			{
				if (data_instance.uuid_parent)
				{
					inp->AddWidgetDataItemUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), *data_instance.uuid_parent, *data_instance.uuid);
				}
				else
				{
					inp->AddWidgetDataItemUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), "", *data_instance.uuid);
				}
			}
		}
		catch (std::bad_cast & bc)
		{
			boost::format msg("Unable to obtain proper widget during construction: %1%");
			msg % bc.what();
			statusManagerUI().PostStatus( msg.str().c_str(), UIStatusManager::IMPORTANCE_HIGH, true );
			return;
		}

		if (IsTopLevel())
		{
			self->connect(project, SIGNAL(RefreshAllWidgets()), self, SLOT(RefreshAllWidgets()));
		}
	}

}

void NewGeneWidget::UpdateOutputConnections(UIProjectManager::UPDATE_CONNECTIONS_TYPE connection_type, UIOutputProject * project)
{

	if (!IsOutputProjectWidget())
	{
		boost::format msg("Attempting to connect an output project to a widget that has not registered as an output widget.");
		statusManagerUI().PostStatus( msg.str().c_str(), UIStatusManager::IMPORTANCE_HIGH, true );
		return;
	}

	if (connection_type == UIProjectManager::RELEASE_CONNECTIONS_OUTPUT_PROJECT)
	{
		if (project && project == outp)
		{
			outp->RemoveWidgetFromUUIDMap(uuid);
			if (data_instance.uuid)
			{
				inp->RemoveWidgetDataItemFromUUIDMap(uuid, *data_instance.uuid);
			}
		}
		outp = nullptr;

		// TODO: release connections here
	}

	else if (connection_type == UIProjectManager::ESTABLISH_CONNECTIONS_OUTPUT_PROJECT)
	{
		outp = project;

		if (!outp)
		{
			statusManagerUI().PostStatus( "Output project is unavailable.", UIStatusManager::IMPORTANCE_HIGH, true );
			return;
		}
		try
		{
			outp->AddWidgetUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), uuid);
			if (data_instance.uuid)
			{
				if (data_instance.uuid_parent)
				{
					outp->AddWidgetDataItemUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), *data_instance.uuid_parent, *data_instance.uuid);
				}
				else
				{
					outp->AddWidgetDataItemUUIDToUUIDMap(dynamic_cast<NewGeneWidget*>(self), "", *data_instance.uuid);
				}
			}
		}
		catch (std::bad_cast & bc)
		{
			boost::format msg("Unable to obtain proper widget during construction: %1%");
			msg % bc.what();
			statusManagerUI().PostStatus( msg.str().c_str(), UIStatusManager::IMPORTANCE_HIGH, true );
			return;
		}

		if (IsTopLevel())
		{
			self->connect(project, SIGNAL(RefreshAllWidgets()), self, SLOT(RefreshAllWidgets()));
		}
	}


}

bool NewGeneWidget::IsInputProjectWidget() const
{
	return widget_nature == WIDGET_NATURE_INPUT_WIDGET;
}

bool NewGeneWidget::IsOutputProjectWidget() const
{
	return widget_nature == WIDGET_NATURE_OUTPUT_WIDGET;
}
