#include"Write_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Write_Action::Write_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Write_Action::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");

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

	pOut->PrintMessage("Enter a variable or a message (in between quotation marks) to be written.");
	while (true)
	{
		Var_Name = pIn->GetString(pOut);
		if (Var_Name[0] == '\"' && Var_Name[Var_Name.size() - 1] == '\"')
			break;
		else if (IsVariable(Var_Name))
			break;
		else
		{
			pOut->ClearStatusBar();
			pOut->PrintMessage("Enter a valid variable or a valid message (in between quotation marks)");
		}
	}
	pOut->ClearStatusBar();
}
void Write_Action::Execute()
{
	ReadActionParameters();
	if (pManager->GetStatCount() == 0) return;		//first statement must be Start statement
	//Calculating left corner of statement block
	Point Corner;
	Corner.x = Position.x;   // top-left of the parallelogram
	Corner.y = Position.y;

	Write_Stat* pwrite = new Write_Stat(Corner, Var_Name);

	pManager->AddStatement(pwrite); // Adds the created statement to application manger's statement list
}