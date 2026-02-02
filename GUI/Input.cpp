
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point& P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

string Input::GetEnterOrEsc(Output* pO) const
{
	string label;
	char Key;
	while (true)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)
			return "esc";
		else if (Key == 13)
			return "ent";
		else
		{
			pO->PrintMessage("Press Enter to Continue or Escape to Abort");
		}
	}
}




double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	double D = 0;
	pO->PrintMessage("Please enter a value");
	while (true)                                 //keep asking until a valid value name is entered
	{
		string input = GetString(pO);
		if (IsValue(input))    //check the validity 
		{
			D = stod(input);
			return D;
		}
		else
		{
			pO->PrintMessage("Please enter a valid value");

		}
	}
}


string Input::GetVariable(Output* pO) const    // Read a variable name from the user
{


	pO->PrintMessage("Please enter a variable name");
	while (true)               //keep asking until a valid variable name is entered
	{
		string input = GetString(pO);
		if (IsVariable(input))   //check the validity 
			return input;
		else
		{
			pO->PrintMessage("please enter a valid variable name");

		}
	}
}



string Input::GetArithOperator(Output* pO) const    // Reads an arithmetic operator from the user
{
	pO->PrintMessage("Please enter an arithmetic operator (+, -, * or /)");
	string key;
	while (true) //keep asking until a valid operator is entered
	{
		key = GetString(pO); //Read an arithmetic operator from the user
		if (key == "+" || key == "-" || key == "*" || key == "/")  //check the validity
		{
			return key;
		}
		else
		{
			pO->PrintMessage("Enter a valid arithmetic operator (+, -, * or /)");
		}

	}
}


string Input::GetCompOperator(Output* pO) const      // Reads comparison operators (==, !=, <, <=, > or >=)
{
	pO->PrintMessage("Please enter comparison operators (==, !=, <, <=, > or >=)");
	while (true)                                         //keep asking until a valid operator is entered
	{
		string oper = GetString(pO);
		if (oper == "==" || oper == "!=" || oper == "<" || oper == "<=" || oper == ">" || oper == ">=")  //check the validity
		{
			return oper;
		}
		else
		{
			pO->PrintMessage("Please enter a valid comparison operators (==, !=, <, <=, > or >=)");

		}
	}
}

string Input::GetVarorVal(Output* pO) const    // Read a variable name from the user
{


	pO->PrintMessage("Please enter a variable or a value");
	while (true)               //keep asking until a valid variable name is entered
	{
		string input = GetString(pO);
		if (IsVariable(input))   //check the validity 
			return input;
		if (IsValue(input))   //check the validity 
			return input;
		else
		{
			pO->PrintMessage("please enter a valid variable name or a valid value");

		}
	}
}
ActionType Input::GetUserAction() const
{
	//This function reads the position where the user clicks to determine the desired action

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check which Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_START: return ADD_START;
			case ITM_END: return ADD_END;
			case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;
			case ITM_VAR_ASSIGN: return ADD_VAR_ASSIGN;
			case ITM_OPER_ASSIGN: return ADD_OPER_ASSIGN;
			case ITM_DECLARE: return ADD_DECLARE_VARIABLE;
			case ITM_COND: return ADD_CONDITION;
			case ITM_READ: return ADD_READ;
			case ITM_WRITE: return ADD_WRITE;
			case ITM_CONNECTOR:return ADD_CONNECTOR;
			case ITM_SELECT:return SELECT;
			case ITM_EDIT_STAT: return EDIT_STAT;
			case ITM_DEL: return DEL;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_SWITCH_SIM_MODE: return SWITCH_SIM_MODE;
			case ITM_EXIT: return EXIT;
			default: return DSN_TOOL;

			}
		}


		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode

	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check which Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);

			switch (ClickedItem)
			{
			case ITM_VALIDATE: return VALIDATE;
			case ITM_RUN: return RUN;
			case ITM_DEBUG: return DEBUG;
			case ITM_GENERATE_CPP: return GENERATE_CPP;
			case ITM_SWITCH_DSN_MODE: return SWITCH_DSN_MODE;
			case ITM_EXITSIM: return EXIT;
			default: return SIM_TOOL;
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}


		return STATUS;
	}

}


Input::~Input()
{
}
