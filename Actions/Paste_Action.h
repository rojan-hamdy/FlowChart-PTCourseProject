#pragma once
#include "Action.h"
#include "..\Statements\Statement.h"

class Paste_Action :public Action
{
private:
	Statement* PastedStatement; // Pointer to the pasted statement
	
	Point Position;
public:
	Paste_Action(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	//paste the statement
	virtual void Execute();

};





