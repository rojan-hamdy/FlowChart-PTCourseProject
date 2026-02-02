#include "Save_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
Save_Action::Save_Action(ApplicationManager* pAppManager) : Action(pAppManager)
{
}
void Save_Action::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	//Read the filename parameter
	pOut->PrintMessage("Save Flowchart: Enter filename to save: ");
	filename = pIn->GetString(pOut);
	pOut->ClearStatusBar();
}
void Save_Action::Execute()
{
	//Read filename to save the flowchart
	ReadActionParameters();
	//Open file to write
	ofstream OutFile;
	OutFile.open(filename + ".txt");
	if (!OutFile.is_open())
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error: Could not open file to save.");
		return;
	}
	//Save the flowchart using ApplicationManager's SaveAll method
	pManager->SaveAll(OutFile);
	OutFile.close();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Flowchart saved to " + filename + ".txt");
}
