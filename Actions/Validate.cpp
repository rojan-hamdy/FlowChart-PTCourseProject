#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Validate::Validate(ApplicationManager* pAppManager) : Action(pAppManager) {}

void Validate::ReadActionParameters() {}

void Validate::Execute()
{
	pManager->validatechart();
}
