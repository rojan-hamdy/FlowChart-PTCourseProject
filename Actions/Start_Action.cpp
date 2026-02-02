#include"Start_Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Start_Action::Start_Action(ApplicationManager* pAppManager) :Action(pAppManager)
{}

void Start_Action::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Start Statement: Click to add the statement");

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
void Start_Action::Execute()
{
	ReadActionParameters();
	//Calculating center of start statement block
	Point Center;

	Center.x = Position.x;
	Center.y = Position.y;

	Start_Stat* pStart = new Start_Stat(Center);
	
	pManager->AddStatement(pStart); // Adds the created statement to application manger's statement list
}