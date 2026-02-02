#pragma once
#include "Action.h"
#include"..\ApplicationManager.h"
class Edit_Action :
    public Action
{
public:
	Edit_Action(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

