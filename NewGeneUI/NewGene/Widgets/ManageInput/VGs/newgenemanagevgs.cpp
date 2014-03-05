#include "newgenemanagevgs.h"
#include "ui_newgenemanagevgs.h"

#include <QStandardItemModel>
#include <QListView>
#include <QDialogButtonBox>

#include "../Project/uiprojectmanager.h"
#include "../Project/uiinputproject.h"
#include "../../Utilities/importdialoghelper.h"
#include "../../../../../NewGeneBackEnd/Utilities/Validation.h"
#include "../../../../NewGeneBackEnd/Utilities/TimeRangeHelper.h"
#include "../../../../NewGeneBackEnd/Model/InputModel.h"
#include "../../../../NewGeneBackEnd/Model/TimeGranularity.h"

NewGeneManageVGs::NewGeneManageVGs( QWidget * parent ) :
	QWidget( parent ),
	NewGeneWidget( WidgetCreationInfo(this, parent, WIDGET_NATURE_INPUT_WIDGET, MANAGE_VGS_WIDGET, true) ), // 'this' pointer is cast by compiler to proper Widget instance, which is already created due to order in which base classes appear in class definition
	ui( new Ui::NewGeneManageVGs )
{
	ui->setupUi( this );
	PrepareInputWidget(true);
}

NewGeneManageVGs::~NewGeneManageVGs()
{
	delete ui;
}

void NewGeneManageVGs::changeEvent( QEvent * e )
{
	QWidget::changeEvent( e );

	switch ( e->type() )
	{
		case QEvent::LanguageChange:
			ui->retranslateUi( this );
			break;

		default:
			break;
	}
}

void NewGeneManageVGs::UpdateInputConnections(NewGeneWidget::UPDATE_CONNECTIONS_TYPE connection_type, UIInputProject * project)
{

	NewGeneWidget::UpdateInputConnections(connection_type, project);

	if (connection_type == NewGeneWidget::ESTABLISH_CONNECTIONS_INPUT_PROJECT)
	{
		connect(this, SIGNAL(RefreshWidget(WidgetDataItemRequest_MANAGE_VGS_WIDGET)), inp->getConnector(), SLOT(RefreshWidget(WidgetDataItemRequest_MANAGE_VGS_WIDGET)));
		connect(project->getConnector(), SIGNAL(WidgetDataRefresh(WidgetDataItem_MANAGE_VGS_WIDGET)), this, SLOT(WidgetDataRefreshReceive(WidgetDataItem_MANAGE_VGS_WIDGET)));
		connect(this, SIGNAL(CreateVG(WidgetActionItemRequest_ACTION_CREATE_VG)), inp->getConnector(), SLOT(AddUOA(WidgetActionItemRequest_ACTION_CREATE_VG)));
		connect(this, SIGNAL(DeleteVG(WidgetActionItemRequest_ACTION_DELETE_VG)), inp->getConnector(), SLOT(DeleteUOA(WidgetActionItemRequest_ACTION_DELETE_VG)));
		connect(this, SIGNAL(RefreshVG(WidgetActionItemRequest_ACTION_REFRESH_VG)), inp->getConnector(), SLOT(DeleteUOA(WidgetActionItemRequest_ACTION_REFRESH_VG)));

		if (project)
		{
			project->RegisterInterestInChange(this, DATA_CHANGE_TYPE__INPUT_MODEL__VG_CHANGE, false, "");
		}
	}
	else if (connection_type == NewGeneWidget::RELEASE_CONNECTIONS_INPUT_PROJECT)
	{
		if (inp)
		{
			inp->UnregisterInterestInChanges(this);
		}
		Empty();
	}

}

void NewGeneManageVGs::UpdateOutputConnections(NewGeneWidget::UPDATE_CONNECTIONS_TYPE connection_type, UIOutputProject * project)
{

	NewGeneWidget::UpdateOutputConnections(connection_type, project);

	if (connection_type == NewGeneWidget::ESTABLISH_CONNECTIONS_OUTPUT_PROJECT)
	{
		if (project)
		{
			connect(this, SIGNAL(DeleteVG(WidgetActionItemRequest_ACTION_DELETE_UOA)), project->getConnector(), SLOT(DeleteVG(WidgetActionItemRequest_ACTION_DELETE_UOA)));
		}
	}
	else if (connection_type == NewGeneWidget::RELEASE_CONNECTIONS_INPUT_PROJECT)
	{
		if (project)
		{
		}
	}

}

void NewGeneManageVGs::RefreshAllWidgets()
{
	if (inp == nullptr)
	{
		Empty();
		return;
	}
	WidgetDataItemRequest_MANAGE_VGS_WIDGET request(WIDGET_DATA_ITEM_REQUEST_REASON__REFRESH_ALL_WIDGETS);
	emit RefreshWidget(request);
}

void NewGeneManageVGs::WidgetDataRefreshReceive(WidgetDataItem_MANAGE_VGS_WIDGET widget_data)
{

	UIInputProject * project = projectManagerUI().getActiveUIInputProject();
	if (project == nullptr)
	{
		return;
	}

	UIMessager messager(project);

	if (!ui->listViewManageVGs)
	{
		boost::format msg("Invalid list view in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	QStandardItemModel * oldModel = static_cast<QStandardItemModel*>(ui->listViewManageVGs->model());
	if (oldModel != nullptr)
	{
		delete oldModel;
	}

	QItemSelectionModel * oldSelectionModel = ui->listViewManageVGs->selectionModel();
	QStandardItemModel * model = new QStandardItemModel(ui->listViewManageVGs);

	int index = 0;
	std::for_each(widget_data.vgs_and_uoa.cbegin(), widget_data.vgs_and_uoa.cend(), [this, &index, &model](std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier> const & vg_and_uoa)
	{
		WidgetInstanceIdentifier const & vg = vg_and_uoa.first;
		WidgetInstanceIdentifier const & uoa = vg_and_uoa.second;
		if (vg.uuid && !vg.uuid->empty() && vg.code && !vg.code->empty())
		{

			QStandardItem * item = new QStandardItem();
			std::string text = Table_VG_CATEGORY::GetVgDisplayText(vg);
			item->setText(text.c_str());
			item->setEditable(false);
			item->setCheckable(false);
			QVariant v;
			v.setValue(vg_and_uoa);
			item->setData(v);
			model->setItem( index, item );

			++index;

		}
	});

	model->sort(0);

	ui->listViewManageVGs->setModel(model);
	if (oldSelectionModel) delete oldSelectionModel;

}

void NewGeneManageVGs::Empty()
{

	if (!ui->listViewManageVGs)
	{
		boost::format msg("Invalid list view in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	QStandardItemModel * oldModel = nullptr;
	QItemSelectionModel * oldSelectionModel = nullptr;

	oldSelectionModel = ui->listViewManageVGs->selectionModel();
	if (oldSelectionModel != nullptr)
	{
		delete oldSelectionModel;
		oldSelectionModel = nullptr;
	}

	oldModel = static_cast<QStandardItemModel*>(ui->listViewManageVGs->model());
	if (oldModel != nullptr)
	{
		delete oldModel;
		oldModel = nullptr;
	}

	oldSelectionModel = ui->listViewManageVGs->selectionModel();
	if (oldSelectionModel != nullptr)
	{
		delete oldSelectionModel;
		oldSelectionModel = nullptr;
	}

}

void NewGeneManageVGs::HandleChanges(DataChangeMessage const & change_message)
{

	UIInputProject * project = projectManagerUI().getActiveUIInputProject();
	if (project == nullptr)
	{
		return;
	}

	UIMessager messager(project);

	if (!ui->listViewManageVGs)
	{
		boost::format msg("Invalid list view in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	QStandardItemModel * itemModel = static_cast<QStandardItemModel*>(ui->listViewManageVGs->model());
	if (itemModel == nullptr)
	{
		boost::format msg("Invalid list view items in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	std::for_each(change_message.changes.cbegin(), change_message.changes.cend(), [this, &itemModel](DataChange const & change)
	{

		switch (change.change_type)
		{

			case DATA_CHANGE_TYPE::DATA_CHANGE_TYPE__INPUT_MODEL__VG_CHANGE:
				{

					switch (change.change_intention)
					{

						case DATA_CHANGE_INTENTION__ADD:
							{

								if (!change.parent_identifier.uuid || (*change.parent_identifier.uuid).empty() || !change.parent_identifier.code || change.parent_identifier.code->empty() || !change.parent_identifier.identifier_parent)
								{
									boost::format msg("Invalid new VG ID, code, or associated UOA.");
									QMessageBox msgBox;
									msgBox.setText( msg.str().c_str() );
									msgBox.exec();
									return;
								}

								WidgetInstanceIdentifier const & vg = change.parent_identifier;
								WidgetInstanceIdentifier const & uoa = *vg.identifier_parent;

								std::string text = Table_VG_CATEGORY::GetVgDisplayText(vg);

								QStandardItem * item = new QStandardItem();
								item->setText(text.c_str());
								item->setEditable(false);
								item->setCheckable(false);

								std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier> vg_and_uoa = std::make_pair(vg, uoa);
								QVariant v;
								v.setValue(vg_and_uoa);
								item->setData(v);
								itemModel->appendRow( item );

							}
							break;

						case DATA_CHANGE_INTENTION__REMOVE:
							{

								if (!change.parent_identifier.uuid || (*change.parent_identifier.uuid).empty() || !change.parent_identifier.code || change.parent_identifier.code->empty() || !change.parent_identifier.identifier_parent)
								{
									boost::format msg("Invalid VG to remove.");
									QMessageBox msgBox;
									msgBox.setText( msg.str().c_str() );
									msgBox.exec();
									return;
								}

								WidgetInstanceIdentifier const & vg = change.parent_identifier;
								WidgetInstanceIdentifier const & uoa = *vg.identifier_parent;

								int numberItems = itemModel->rowCount();
								for(int currentItem = 0; currentItem < numberItems; ++currentItem)
								{
									QStandardItem * vg_to_remove_item = itemModel->item(currentItem);
									if (vg_to_remove_item != nullptr)
									{

										QVariant vg_and_uoa_variant = vg_to_remove_item->data();
										std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier> const vg_and_uoa = vg_and_uoa_variant.value<std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier>>();
										WidgetInstanceIdentifier const & vg_test = change.parent_identifier;
										if (!vg_test.identifier_parent)
										{
											continue;
										}
										WidgetInstanceIdentifier const & uoa_test = *vg_test.identifier_parent;

										if (vg_test.IsEqual(WidgetInstanceIdentifier::EQUALITY_CHECK_TYPE__UUID_PLUS_STRING_CODE, vg)
											&&
											uoa_test.IsEqual(WidgetInstanceIdentifier::EQUALITY_CHECK_TYPE__UUID_PLUS_STRING_CODE, uoa))
										{

											QModelIndex index_to_remove = itemModel->indexFromItem(vg_to_remove_item);
											itemModel->takeRow(index_to_remove.row());

											delete vg_to_remove_item;
											vg_to_remove_item = nullptr;

											QItemSelectionModel * selectionModel = ui->listViewManageVGs->selectionModel();
											if (selectionModel != nullptr)
											{
												selectionModel->clearSelection();
											}

											break;

										}

									}
								}

							}
							break;

						case DATA_CHANGE_INTENTION__UPDATE:
							{
								// Should never receive this.
							}
							break;

						case DATA_CHANGE_INTENTION__RESET_ALL:
							{
								// Ditto above.
							}
							break;

						default:
							{
							}
							break;

					}

				}
				break;

			default:
				{
				}
				break;

		}

	});

}

bool NewGeneManageVGs::GetSelectedVG(WidgetInstanceIdentifier & vg, WidgetInstanceIdentifier & uoa)
{

	QItemSelectionModel * vg_selectionModel = ui->listViewManageVGs->selectionModel();
	if (vg_selectionModel == nullptr)
	{
		boost::format msg("Invalid selection in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return false;
	}

	QModelIndex selectedIndex = vg_selectionModel->currentIndex();
	if (!selectedIndex.isValid())
	{
		// No selection
		return false;
	}

	QStandardItemModel * vgModel = static_cast<QStandardItemModel*>(ui->listViewManageVGs->model());
	if (vgModel == nullptr)
	{
		boost::format msg("Invalid model in NewGeneManageVGs DMU category widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return false;
	}

	QVariant vg_and_uoa_variant = vgModel->item(selectedIndex.row())->data();
	std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier> vg_and_uoa = vg_and_uoa_variant.value<std::pair<WidgetInstanceIdentifier, WidgetInstanceIdentifier>>();
	vg = vg_and_uoa.first;
	if (!vg.identifier_parent)
	{
		return false;
	}
	uoa = *vg.identifier_parent;

	return true;

}

void NewGeneManageVGs::on_pushButton_add_vg_clicked()
{

	UIInputProject * project = projectManagerUI().getActiveUIInputProject();
	if (project == nullptr)
	{
		boost::format msg("Bad input project.  Unable to create \"New VG\" dialog.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	UIInputModel & ui_input_model = project->model();
	InputModel & backend_input_model = ui_input_model.getBackendModel();
	WidgetInstanceIdentifiers dmu_categories = backend_input_model.t_dmu_category.getIdentifiers();

	// From http://stackoverflow.com/a/17512615/368896
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("Create new variable group"));
	QList<QLineEdit *> fields;
	QLineEdit *lineEditCode = new QLineEdit(&dialog);
	QString labelCode = QString("Enter a brief identifying code for the new variable group (all caps):");
	form.addRow(labelCode, lineEditCode);
	fields << lineEditCode;

	QLineEdit *lineEditDescription = new QLineEdit(&dialog);
	QString labelDescription = QString("Description:");
	form.addRow(labelDescription, lineEditDescription);
	fields << lineEditDescription;

	QWidget VgConstructionWidget;
	QVBoxLayout formOverall;
	QWidget VgConstructionPanes;
	QHBoxLayout formConstructionPane;
	QVBoxLayout formConstructionButtons;
	QListView * listpane = nullptr;
	ImportDialogHelper::AddVgCreationBlock(dialog, form, VgConstructionWidget, formOverall, VgConstructionPanes, formConstructionPane, formConstructionButtons, listpane);

	if (!listpane)
	{
		boost::format msg("Unable to create \"New VG\" dialog.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);

	std::string proposed_vg_code;
	std::string vg_description;

	WidgetInstanceIdentifier uoa_to_use;

	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	QObject::connect(&buttonBox, &QDialogButtonBox::accepted, [&]()
	{

		std::string errorMsg;

		QLineEdit * proposed_vg_code_field = fields[0];
		QLineEdit * vg_description_field = fields[1];
		if (proposed_vg_code_field && vg_description_field)
		{
			proposed_vg_code = proposed_vg_code_field->text().toStdString();
			vg_description = vg_description_field->text().toStdString();
			if (proposed_vg_code.empty())
			{
				boost::format msg("The VG must have an identifying code (typically, a short, all-caps string).");
				QMessageBox msgBox;
				msgBox.setText( msg.str().c_str() );
				msgBox.exec();
				return false;
			}
		}
		else
		{
			boost::format msg("Unable to determine new VG code or description.");
			QMessageBox msgBox;
			msgBox.setText( msg.str().c_str() );
			msgBox.exec();
			return false;
		}

		boost::trim(proposed_vg_code);
		boost::trim(vg_description);

		bool valid = true;

		if (valid)
		{
			valid = Validation::ValidateVgCode(proposed_vg_code, errorMsg);
		}

		if (valid)
		{
			valid = Validation::ValidateVgDescription(vg_description, errorMsg);
		}

		if (!valid)
		{
			boost::format msg("%1%");
			msg % errorMsg;
			QMessageBox msgBox;
			msgBox.setText( msg.str().c_str() );
			msgBox.exec();
			return false;
		}

		if (valid)
		{

			// retrieve the UOA to associate with the new variable group
			QStandardItemModel * listpaneModel = static_cast<QStandardItemModel*>(listpane->model());
			if (listpaneModel == nullptr)
			{
				boost::format msg("Invalid list view items in Construct VG popup.");
				QMessageBox msgBox;
				msgBox.setText( msg.str().c_str() );
				msgBox.exec();
				return false;
			}

			QItemSelectionModel * listpane_selectionModel = listpane->selectionModel();
			if (listpane_selectionModel == nullptr)
			{
				boost::format msg("Invalid selection in New VG popup.");
				QMessageBox msgBox;
				msgBox.setText( msg.str().c_str() );
				msgBox.exec();
				return false;
			}

			QModelIndex selectedIndex = listpane_selectionModel->currentIndex();
			if (!selectedIndex.isValid())
			{
				boost::format msg("A unit of analysis must be associated with the new variable group.");
				QMessageBox msgBox;
				msgBox.setText( msg.str().c_str() );
				msgBox.exec();
				return false;
			}

			QVariant uoa_variant = listpaneModel->item(selectedIndex.row())->data();
			uoa_to_use = uoa_variant.value<WidgetInstanceIdentifier>();

			dialog.accept();
		}

	});

	if (dialog.exec() != QDialog::Accepted)
	{
		return;
	}

	std::string new_vg_code(proposed_vg_code);

	InstanceActionItems actionItems;
	actionItems.push_back(std::make_pair(uoa_to_use, std::shared_ptr<WidgetActionItem>(static_cast<WidgetActionItem*>(new WidgetActionItem_StringVector(std::vector<std::string>{new_vg_code, vg_description})))));
	WidgetActionItemRequest_ACTION_CREATE_VG action_request(WIDGET_ACTION_ITEM_REQUEST_REASON__ADD_ITEMS, actionItems);

	emit CreateVG(action_request);

}

void NewGeneManageVGs::on_pushButton_remove_vg_clicked()
{

	UIInputProject * project = projectManagerUI().getActiveUIInputProject();
	if (project == nullptr)
	{
		return;
	}

	UIMessager messager(project);

	if (!ui->listViewManageVGs)
	{
		boost::format msg("Invalid list view in NewGeneManageVGs widget.");
		QMessageBox msgBox;
		msgBox.setText( msg.str().c_str() );
		msgBox.exec();
		return;
	}

	WidgetInstanceIdentifier vg;
	WidgetInstanceIdentifier uoa;
	bool is_selected = GetSelectedVg(vg, uoa);
	if (!is_selected)
	{
		return;
	}

	InstanceActionItems actionItems;
	actionItems.push_back(std::make_pair(vg, std::shared_ptr<WidgetActionItem>(static_cast<WidgetActionItem*>(new WidgetActionItem()))));
	WidgetActionItemRequest_ACTION_DELETE_VG action_request(WIDGET_ACTION_ITEM_REQUEST_REASON__REMOVE_ITEMS, actionItems);
	emit DeleteVG(action_request);

}

void NewGeneManageVGs::on_pushButton_refresh_vg_clicked()
{

}
