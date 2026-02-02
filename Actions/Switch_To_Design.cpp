#include "Switch_To_Design.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"

Switch_To_Design::Switch_To_Design(ApplicationManager* pAppManager) : Action(pAppManager) {}
void Switch_To_Design::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Switch To Design Mode.");
	pOut->CreateDesignToolBar();
}
void Switch_To_Design::Execute()
{
	UI.AppMode = DESIGN;
	Output* pOut = pManager->GetOutput();
	pOut->ClearOutputBar();
	ReadActionParameters();
}
