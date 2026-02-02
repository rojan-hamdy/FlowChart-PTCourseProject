#pragma once
#include "Action.h"
class Debug :
    public Action
{
public:
	Debug(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

