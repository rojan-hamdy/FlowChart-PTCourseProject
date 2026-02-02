#include "Paste_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action
Paste_Action::Paste_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Paste_Action::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Paste Action:Click any where to Add the (cut/copied) Statement.");

	while (true)
	{

		pIn->GetPointClicked(Position);

		bool insideDrawingArea =
			Position.y >= UI.ToolBarHeight &&
			Position.y <= UI.height - UI.StatusBarHeight &&
			Position.x >= 0 &&
			Position.x <= UI.DrawingAreaWidth;

		// Check 1: must be inside drawing area
		if (!insideDrawingArea)
		{
			pOut->PrintMessage("Invalid! Click inside the drawing area.");
			continue;
		}

		// Check 2: must NOT be on another statement
		if (pManager->GetStatement(Position) != NULL)
		{
			pOut->PrintMessage("There is already a statement here:Click somewhere else.");
			continue;
		}

		// Valid
		break;
	}
	pOut->ClearStatusBar();
	
}
void Paste_Action::Execute()  
{
	//Read the position clicked
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	Statement* copied = pManager->GetClipboard();   //Pointer to the copied\cutted statement
	if (!copied) {
		pOut->PrintMessage("Clipboard is empty.");
		return;
	}
	// Get clone
	PastedStatement = copied->Clone(Position);
	//Add the pasted statement to the list of statments 
	pManager->AddStatement(PastedStatement);
	pOut->PrintMessage("Statement pasted successfully.");
}
