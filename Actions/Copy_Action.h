#pragma once
#include "Action.h"
#include"..\Actions\SelectAction.h"
class Copy_Action :
    public Action
{
private:
	Statement* selectedStatement; // Pointer to the selected statement
	Connector* selectedConnector; // Pointer to the selected connector

public:
	Copy_Action(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	//Copy the selected statement 
	virtual void Execute();
};
