#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar

	//TODO: Complete the following 2 functions
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode

	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearOutputBar(); //Clears the Output bar

	void PrintMessage(string msg);	//Prints a message on Status bar
	void DrawString(const int, const int, const string, const color col = BLACK);  //Writes a string in the specified location

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected = false);

	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
	//		Decide the parameters that should be passed to each of them
	void DrawDeclareStat(Point Left, int width, int height, string Text, bool Selected = false);
	void DrawStart(const int ix, const int iy, bool Selected = false);
	void DrawEnd(const int ix, const int iy, bool Selected = false);
	void DrawCondtionalStat(const int ix, const int iy, string text, bool Selected = false);
	void DrawRead(const int ix, const int iy, string text, bool Selected = false);
	void DrawWrite(const int ix, const int iy, string text, bool Selected = false);

	//TODO: Add DrawConnector function
	void DrawConnector(const int xStart, const int yStart, const int xEnd, const int yEnd, bool Selected = false);

	~Output();
};

#endif