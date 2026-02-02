#include "AddOperatorAssign.h"
#include "..\ApplicationManager.h"


#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddOperatorAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

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
	
	//  Read LHS using Input::GetVariable (already validated)

	LHS = pIn->GetVariable(pOut);
	pOut->ClearStatusBar();
	
	//  Read first operand from the user
	firstoper = pIn->GetVarorVal(pOut);
	pOut->ClearStatusBar();

	// read the operator from the user
	operation = pIn->GetArithOperator(pOut);
	pOut->ClearStatusBar();
	
	//  Read second operand from the user
	secondoper = pIn->GetVarorVal(pOut);
	pOut->ClearStatusBar();
}

void AddOperatorAssign::Execute()
{
	ReadActionParameters();
	if (pManager->GetStatCount() == 0) return;		//first statement must be Start statement


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	OperatorAssign* pAssign = new OperatorAssign(Corner, LHS, firstoper, operation, secondoper);
	

	
	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

