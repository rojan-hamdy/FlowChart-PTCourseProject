#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "..\Statements\Start_Stat.h"

class Start_Action : public Action
{
private : 
	Point Position; 
public :
	Start_Action(ApplicationManager* pAppManager);


	//Read Start statements position
	virtual void ReadActionParameters();

	//Create and add an start statement to the list of statements
	virtual void Execute();
};
#endif