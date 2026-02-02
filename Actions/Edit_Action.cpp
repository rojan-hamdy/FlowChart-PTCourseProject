#include "Edit_Action.h"
#include "../Statements/Statement.h"
#include"..\ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
Edit_Action::Edit_Action(ApplicationManager* pApp) : Action(pApp)
{
}
void Edit_Action::ReadActionParameters()
{
}
void Edit_Action::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	
	Statement* pSelectedStat = pManager->GetSelectedStatement();
	if (!pSelectedStat)
	{
		pOut->PrintMessage("No statement selected to edit.");
		return;
	}
	pSelectedStat->Edit(pIn, pOut);
	pSelectedStat->SetSelected(false); //deselect the statement after editing
	pManager->SetSelectedStatement(nullptr); //deselect the statement after editing
	pManager->UpdateInterface();
	
}