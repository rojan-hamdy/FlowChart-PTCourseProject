#pragma once
#include "Action.h"
class Switch_To_Sim : public Action
{
public:
	Switch_To_Sim(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};