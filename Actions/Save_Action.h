#pragma once
#include "Action.h"
class Save_Action :
    public Action
{
private:
	string filename;
    public:
    Save_Action(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
	virtual void Execute();
};

