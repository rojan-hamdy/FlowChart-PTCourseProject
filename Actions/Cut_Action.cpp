#include "Cut_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action
Cut_Action::Cut_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Cut_Action::ReadActionParameters()
{

}
void Cut_Action::Execute()  
{
	 
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	selectedStatement = pManager->GetSelectedStatement();
	selectedConnector = pManager->GetSelectedConnector();
	//Case:selected is statement
	if (selectedStatement)
	{
		Point p(0, 0);
		pManager->SetClipboard(selectedStatement->Clone(p));   // pointer to the selected statment and clone to save it's info before delete 
		pManager->Delete_Stat(selectedStatement);   // delete the statement and its connrctors
		pOut->PrintMessage("Statement is cutted successfully.");

	}
	//Case:selected is connector
	else if (selectedConnector)
	{
		pOut->PrintMessage("Cannot cut connector: Action Aborted.");
	}
	//Case:nothing is selected
	else
	{
		pOut->PrintMessage("No statement is selected:Click Select action First.");
	}

	pManager->SetSelectedStatement(nullptr);
	pManager->SetSelectedConnector(nullptr);
	//update the interface to the one after cutting
	pManager->UpdateInterface();
}