#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\HelperFn.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;   //Class forward declaration
class Input		//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Input(window* pW);		//Consturctor
	void GetPointClicked(Point& P) const;//Gets coordinate where user clicks


	double GetValue(Output* pO) const;	// Reads a double value from the user 

	string GetString(Output* pO) const; //Returns a string entered by the user

	string GetEnterOrEsc(Output* pO) const;	//Returns a string indicating whether pressed key is enter or escape

	string GetVariable(Output* pO) const;  //Reads variable name from the user

	string GetVarorVal(Output* pO) const;  //Reads variable name or value from the user

	string GetArithOperator(Output* pO) const; // Reads an arithmetic operator from the user

	string GetCompOperator(Output* pO) const; // Reads a comparison operator from the user



	ActionType GetUserAction() const; //Reads the user click and maps it to an action

	~Input();
};

#endif