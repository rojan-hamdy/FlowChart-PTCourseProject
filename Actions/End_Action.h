#ifndef ADD_END_H
#define ADD_END_H

#include "Action.h"
#include "..\Statements\End_Stat.h"

class End_Action : public Action
{
private:
	Point Position;
public:
	End_Action(ApplicationManager* pAppManager);


	//Read Start statements position
	virtual void ReadActionParameters();

	//Create and add an start statement to the list of statements
	virtual void Execute();
};
#endif