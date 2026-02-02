#include"Read_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Read_Action::Read_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Read_Action::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");

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

		// Check 3: first statement MUST be a Start statement
		if (pManager->GetStatCount() == 0)
		{
			pOut->PrintMessage("First statement must be a Start statement.");
			return;
		}

		// Valid
		break;
	}
	pOut->ClearStatusBar();
	Var_Name = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
}
void Read_Action::Execute()
{
	ReadActionParameters();
	if (pManager->GetStatCount() == 0) return;		//first statement must be Start statement
	//Calculating left corner of statement block
	Point Corner;
	Corner.x = Position.x;   // top-left of the parallelogram
	Corner.y = Position.y;

	Read_Stat* pread = new Read_Stat(Corner, Var_Name);

	pManager->AddStatement(pread); // Adds the created statement to application manger's statement list
}