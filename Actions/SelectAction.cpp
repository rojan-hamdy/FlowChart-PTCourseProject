#include "SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
SelectAction::SelectAction(ApplicationManager* pAppManager) : Action(pAppManager)
{

}
void SelectAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Select Statement: Click to select a statement or connector");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//intialize selectedStatement and selectedConnector to nullptr
	selectedStatement = nullptr;
	selectedConnector = nullptr;

	//check if a statement is selected
	selectedStatement = pManager->GetStatement(Position);
	//if no statement is selected, check for connector
	if (!selectedStatement)
	{
		selectedConnector = pManager->GetConnector(Position);
	}

}
void SelectAction::Execute()
{
	//Read click position and detect selected statement or connector
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	//Get previously selected statement and connector
	Statement* prevStat = pManager->GetSelectedStatement();
	Connector* prevConn = pManager->GetSelectedConnector();

	//Case1: A statement is selected
	if (selectedStatement)
	{
		//unselect if already selected
		if (selectedStatement == prevStat)
		{
			selectedStatement->SetSelected(false);
			pManager->SetSelectedStatement(nullptr);
			pOut->PrintMessage("Statement unselected");
		}
		else //select the new statement
		{
			//unselect previous statement if any
			if (prevStat)
			{
				prevStat->SetSelected(false);
				pManager->SetSelectedStatement(nullptr);
			}
			//unselect previous connector if any
			if (prevConn)
			{
				prevConn->SetSelected(false);
				pManager->SetSelectedConnector(nullptr);
			}
			//select the new statement
			selectedStatement->SetSelected(true);
			pManager->SetSelectedStatement(selectedStatement);
			pOut->PrintMessage("Statement selected");
		}
		pManager->UpdateInterface();
		return;
	}
	//Case2: A connector is selected
	else if (selectedConnector)
	{
		//unselect if already selected
		if (selectedConnector == prevConn)
		{
			selectedConnector->SetSelected(false);
			pManager->SetSelectedConnector(nullptr);
			pOut->PrintMessage("Connector unselected");
		}
		else //select the new connector
		{
			//unselect previous connector if any
			if (prevConn)
			{
				prevConn->SetSelected(false);
				pManager->SetSelectedConnector(nullptr);
			}
			//unselect previous statement if any
			if (prevStat)
			{
				prevStat->SetSelected(false);
				pManager->SetSelectedStatement(nullptr);
			}
			//select the new connector
			selectedConnector->SetSelected(true);
			pManager->SetSelectedConnector(selectedConnector);
			pOut->PrintMessage("Connector selected");
		}
		pManager->UpdateInterface();
		return;
	}
	//case3 click on empty area
	pOut->PrintMessage("Nothing selected");
}