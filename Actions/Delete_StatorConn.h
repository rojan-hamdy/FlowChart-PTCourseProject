#include "Action.h"
#include"..\Actions\SelectAction.h"

class Delete_StatorConn : public Action
{
private:
	Statement* selectedStatement; // Pointer to the selected statement
	Connector* selectedConnector; // Pointer to the selected connector
	
public:
	Delete_StatorConn(ApplicationManager* pAppManager);


	
	virtual void ReadActionParameters();

	//Delete the selected statement or connector
	virtual void Execute();
	
};
