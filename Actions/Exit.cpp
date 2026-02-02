#include "Exit.h"
#include "../ApplicationManager.h"

Exit::Exit(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Exit::ReadActionParameters()
{
}

void Exit::Execute()
{
	pManager->clearflowchart();
	exit(0);
}
