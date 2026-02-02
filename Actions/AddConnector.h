#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include"..\Connector.h"
class AddConnector :
    public Action
{
    private:
    Statement* Src; //The source statement of the connector
	Statement* Dst1; //The destination statement of the connector
	Statement* Dst2; //The destination statement of the connector
	bool canceled; //Flag to check if the action was canceled
public:
    AddConnector(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
	virtual void Execute();
};

