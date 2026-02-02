#include"Delete_StatorConn.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete_StatorConn::Delete_StatorConn(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Delete_StatorConn::ReadActionParameters()
{

}
void Delete_StatorConn::Execute() 
{
	
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	selectedStatement = pManager->GetSelectedStatement();
	selectedConnector = pManager->GetSelectedConnector();
	//Case:selected is statement
	if (selectedStatement)
	{
		
		pManager->Delete_Stat(selectedStatement);
		pOut->PrintMessage("Statement and its connector deleted successfully");
	}
	else if (selectedConnector)
	{
		pManager->Delete_Conn(selectedConnector);
		pOut->PrintMessage("Connector deleted successfully");
	}
	else
	{
		pOut->PrintMessage("No statement or connector selected:Click Select action First.");
	}

	pManager->SetSelectedStatement(nullptr);
	pManager->SetSelectedConnector(nullptr);
	//update the interface to the one after deletion
	pManager->UpdateInterface();	
}

