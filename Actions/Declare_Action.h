#ifndef ADD_DECLARE_VARIABLE_H
#define ADD_DECLARE_VARIABLE_H

#include "Action.h"
#include "..\Statements\Declare_Stat.h"

class Declare_Action : public Action
{
private:
	Point Position;
	string Var_Name;     // variable name
public:
	Declare_Action(ApplicationManager* pAppManager);


	//Read Declare statements position
	virtual void ReadActionParameters();

	//Create and add an declare statement to the list of statements
	virtual void Execute();
};
#endif