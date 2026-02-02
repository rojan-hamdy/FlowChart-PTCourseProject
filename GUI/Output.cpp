#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1400; 
	UI.height = 650; 
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 58;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(RED, 3);

	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode

	//clearing the toolbar by drawing a filled white rectangle
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	//fill the tool bar 

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\Start.jpg";
	MenuItemImages[ITM_END] = "images\\End.jpg";
	MenuItemImages[ITM_DECLARE] = "images\\Declare.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\VarAssign.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\OpAssign.jpg";
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";
	MenuItemImages[ITM_READ] = "images\\Read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\Connector.jpg";
	MenuItemImages[ITM_SELECT] = "images\\Select.jpg";
	MenuItemImages[ITM_EDIT_STAT] = "images\\Edit.jpg";
	MenuItemImages[ITM_DEL] = "images\\Delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\Cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Load.jpg";
	MenuItemImages[ITM_SWITCH_SIM_MODE] = "images\\SimMode.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < DSN_ITM_CNT; i++)        //draw images on the toolbar
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//clearing the toolbar by drawing a filled white rectangle
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	string SimItemImages[SIM_ITM_CNT];
	SimItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
	SimItemImages[ITM_RUN] = "images\\Run.jpg";
	SimItemImages[ITM_DEBUG] = "images\\Debug.jpg";
	SimItemImages[ITM_GENERATE_CPP] = "images\\Generatecpp.jpg";
	SimItemImages[ITM_SWITCH_DSN_MODE] = "images\\DesignMode.jpg";
	SimItemImages[ITM_EXITSIM] = "images\\Exit.jpg";

	for (int i = 0; i < SIM_ITM_CNT; i++)
		pWind->DrawImage(SimItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text, const color col)
{
	pWind->SetPen(col, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}

void Output::DrawDeclareStat(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}

void Output::DrawStart(const int ix, const int iy, bool Selected)
{
	const int Radius = 30;
	if (Selected)     //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);      //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);    //use normal color

	//Draw the statement Circle, centered at ix, iy, unfilled (FRAME)
	pWind->DrawCircle(ix, iy, Radius, FRAME);

	//Write Start
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(ix - 20, iy - 10, "Start");
}

void Output::DrawEnd(const int ix, const int iy, bool Selected)
{
	const int Radius = 30;
	if (Selected)     //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);      //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);    //use normal color

	//Draw the statement Circle, centered at ix, iy, unfilled (FRAME)
	pWind->DrawCircle(ix, iy, Radius, FRAME);

	//Write End
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(ix - 15, iy - 10, "End");
}

void Output::DrawCondtionalStat(const int ix, const int iy, string text, bool Selected)
{
	const int xDiff = 50, yDiff = 90;
	//create an array of points to draw the diamond shape (starting from the top vertix, going anti-clockwise)
	int arrx[4] = { ix, ix - xDiff, ix, ix + xDiff };
	int arry[4] = { iy, iy + yDiff / 2, iy + yDiff, iy + yDiff / 2 };
	if (Selected)     //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);      //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);    //use normal color

	//Draw the shape of the conditional statement
	pWind->DrawPolygon(arrx, arry, 4, FRAME);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(ix - 20, iy + 30, text);
}

void Output::DrawRead(const int ix, const int iy, string text, bool Selected)
{
	//smallxDiff: distance between two points above each other, largexDiff: distance between two points next to each other
	int smallxDiff = 30, largexDiff = 70, yDiff = 50;
	//create an array of points to draw the parallelogram shape
	int arrx[4] = { ix + largexDiff + smallxDiff, ix + largexDiff, ix - smallxDiff, ix };
	int arry[4] = { iy, iy + yDiff, iy + yDiff, iy };
	if (Selected)     //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);      //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);    //use normal color

	//Draw the shape of the Read statement
	pWind->DrawPolygon(arrx, arry, 4, FRAME);

	//Read statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(ix, iy + 15, "Read " + text);
}

void Output::DrawWrite(const int ix, const int iy, string text, bool Selected)
{
	//smallxDiff: distance between two points above each other, largexDiff: distance between two points next to each other
	int smallxDiff = 30, largexDiff = 70, yDiff = 50;
	//create an array of points to draw the parallelogram shape
	int arrx[4] = { ix + largexDiff + smallxDiff, ix + largexDiff, ix - smallxDiff, ix };
	int arry[4] = { iy, iy + yDiff, iy + yDiff, iy };
	if (Selected)     //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);      //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);    //use normal color

	//Draw the shape of the Write statement
	pWind->DrawPolygon(arrx, arry, 4, FRAME);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(ix, iy + 15, "Write " + text);
}

void Output::DrawConnector(const int xStart, const int yStart, const int xEnd, const int yEnd, bool Selected)
{
	{
		// Choose color
		if (Selected)
			pWind->SetPen(UI.HighlightColor, 3);
		else
			pWind->SetPen(UI.DrawColor, 3);

		// ---------------------------------------------
		//  CASE 1 — LOOP (destination is ABOVE source)
		// ---------------------------------------------
		if (yEnd < yStart)
		{
			bool loopRight = (xEnd >= xStart);
			int offset = 40;
			int dx = loopRight ? offset : -offset;

			Point p1 = { xStart, yStart };
			Point p2 = { xStart + dx, yStart };
			Point p3 = { p2.x, yEnd };
			Point p4 = { xEnd, yEnd };

			// Draw loop (4 segments)
			pWind->DrawLine(p1.x, p1.y, p2.x, p2.y);
			pWind->DrawLine(p2.x, p2.y, p3.x, p3.y);
			pWind->DrawLine(p3.x, p3.y, p4.x, p4.y);

			// Arrow head (always pointing DOWN)
			const int A = 7;
			pWind->DrawTriangle(
				xEnd, yEnd,
				xEnd - A, yEnd - A,
				xEnd + A, yEnd - A
			);

			return;
		}

		// ---------------------------------------------
		//  CASE 2 — NORMAL L-SHAPE CONNECTOR
		// ---------------------------------------------
		Point mid = { xEnd, yStart };

		pWind->DrawLine(xStart, yStart, mid.x, mid.y);
		pWind->DrawLine(mid.x, mid.y, xEnd, yEnd);

		// Arrow head
		const int A = 7;
		pWind->DrawTriangle(
			xEnd, yEnd,
			xEnd - A, yEnd - A,
			xEnd + A, yEnd - A
		);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
