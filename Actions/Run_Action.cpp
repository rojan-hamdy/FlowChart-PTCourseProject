#include "Run_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Run_Action::Run_Action(ApplicationManager* pAppManager) : Action(pAppManager) {}

void Run_Action::ReadActionParameters() {}

void Run_Action::Execute()
{
	bool isvalid = pManager->validatechart();
	if (isvalid)
	{
		pManager->runchart();
	}
}
