#ifndef UIMODELMANAGER_H
#define UIMODELMANAGER_H

#include "globals.h"
#include "uimanager.h"
#include "..\..\..\NewGeneBackEnd\Model\ModelManager.h"

class NewGeneMainWindow;

class UIInputModel;

class UIOutputModel;

template<typename MODEL_CLASS>
class UIModel;

class UIModelManager : public QObject, public UIManager<UIModelManager, ModelManager, MANAGER_DESCRIPTION_NAMESPACE::MANAGER_MODEL_UI, MANAGER_DESCRIPTION_NAMESPACE::MANAGER_MODEL>
{
		Q_OBJECT
	public:
		explicit UIModelManager( QObject * parent = 0 );

		UIInputModel * loadDefaultModel();

	signals:

	public slots:

	private:

};

#endif // UIMODELMANAGER_H
