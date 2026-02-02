#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"

class GeneratecppAction :public Action
{
private:

public:
	GeneratecppAction(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	//Generate cpp file
	virtual void Execute();

};





