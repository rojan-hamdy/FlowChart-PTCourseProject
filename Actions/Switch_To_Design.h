#pragma once
#include "Action.h"
class Switch_To_Design : public Action
{
public:
	Switch_To_Design(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};

