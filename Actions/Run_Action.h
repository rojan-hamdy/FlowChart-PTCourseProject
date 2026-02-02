#pragma once
#include "Action.h"
class Run_Action :
	public Action
{
public:
	Run_Action(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

