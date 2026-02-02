#include "AddCondition.h"
#include "..\ApplicationManager.h"


#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCondition::AddCondition(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddCondition::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");

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
	pOut->PrintMessage("Enter only if or while (no capital letters)");
	while (true)
	{
		
		type = pIn->GetString(pOut);
		if (type != "if" && type != "while") 
		{
			pOut->PrintMessage("Enter only if or while (no capital letters)");
		
		}
		else
		{
			break; 
		}
	}
		//  Read LHS using Input::GetVariable (already validated)
		LHS = pIn->GetVariable(pOut);
		pOut->ClearStatusBar();

		// Read Comparison operator from the user
		comparison = pIn->GetCompOperator(pOut);
		pOut->ClearStatusBar();
		//Read RLS  using Input::GetVarorVal (already validated)
		RHS = pIn->GetVarorVal(pOut);
		pOut->ClearStatusBar();
	}

void AddCondition::Execute()
{
	ReadActionParameters();
	if (pManager->GetStatCount() == 0) return;		//first statement must be Start statement


	//Calculating left corner of condition statement block
	Point Corner;
	// The "corner" for a diamond = top vertex
	Corner.x = Position.x;   // top vertex x
	Corner.y = Position.y;   // top vertex y

	Condition_Stat* pcond = new Condition_Stat(Corner, LHS,comparison, RHS,type);

	pManager->AddStatement(pcond); // Adds the created statement to application manger's statement list
}

