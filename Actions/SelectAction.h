#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Connector.h"
class SelectAction :
    public Action
{
private:
	Statement* selectedStatement; // Pointer to the selected statement
	Connector* selectedConnector; // Pointer to the selected connector
	Point Position; // Position where the user clicks to select
    public:
    SelectAction(ApplicationManager* pAppManager);
    //Reads Select Action parameters
    virtual void ReadActionParameters(); 
    //Execute Select Action
	virtual void Execute();
};

