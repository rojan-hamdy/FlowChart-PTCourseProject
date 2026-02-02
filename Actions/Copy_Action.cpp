#include "Copy_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action
Copy_Action::Copy_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Copy_Action::ReadActionParameters()
{

}
void Copy_Action::Execute()  
{
	
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	selectedStatement = pManager->GetSelectedStatement();
	selectedConnector = pManager->GetSelectedConnector();
	//Case:selected is statement
	if (selectedStatement)       
	{
		Statement* currentstat = selectedStatement->Clone(selectedStatement->GetInPoint()); //clone for the statement before any edit 
		// position will be edited later by the paste 
		pManager->SetClipboard(currentstat);
		pOut->PrintMessage("Statement is copied successfully");
		selectedStatement->SetSelected(false); // unselect the statement after doing the action
	}
	//Case:selected is connector
	else if (selectedConnector)
	{
		pOut->PrintMessage("Cannot copy connector: Action Aborted");
	}
	//Case:nothing is selected
	else
	{
		pOut->PrintMessage("No statement is selected:Click Select action First.");
	}

	pManager->SetSelectedStatement(nullptr);
	pManager->SetSelectedConnector(nullptr);
	
}