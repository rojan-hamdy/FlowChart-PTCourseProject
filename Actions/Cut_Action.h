#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\Connector.h"
class Cut_Action :public Action
{
private:
	Statement* selectedStatement; // Pointer to the selected statement
	Connector* selectedConnector; // Pointer to the selected connector

public:
	Cut_Action(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	//Cut the selected statement 
	virtual void Execute();
};
