#include "Debug.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Debug::Debug(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Debug::ReadActionParameters()
{
}

void Debug::Execute()
{
	bool isvalid = pManager->validatechart();
	if (isvalid)
	{
		pManager->debugchart();
	}
}