#pragma once
#include "Action.h"
class Exit :
    public Action
{
    public:
    Exit(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
	virtual void Execute();
};

