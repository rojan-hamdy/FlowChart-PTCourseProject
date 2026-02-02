#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_DECLARE_VARIABLE, // Add  declare variable statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements

	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	SWITCH_DSN_MODE,	//Switch to Design mode
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application


	//NOTE: BONUS ITEMS MAY BE ADDED LATER
	VALIDATE,
	RUN,
	DEBUG,
	GENERATE_CPP,

	DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	SIM_TOOL,
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	STATUS 		   //A click on the status bar
};

enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_START,
	ITM_END,
	ITM_DECLARE,
	ITM_VALUE_ASSIGN,//simple assignment statement
	ITM_VAR_ASSIGN,
	ITM_OPER_ASSIGN,
	ITM_COND,		//conditional statement
	ITM_READ,
	ITM_WRITE,
	ITM_CONNECTOR,
	ITM_SELECT,
	ITM_EDIT_STAT,
	ITM_DEL,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_SAVE,
	ITM_LOAD,
	ITM_SWITCH_SIM_MODE,
	ITM_EXIT,		//Exit

	//Note: bonus items may be added later

	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum

};

enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run

	//NOTE: BONUS ITEMS MAY BE ADDED LATER
	ITM_DEBUG,
	ITM_GENERATE_CPP,
	ITM_SWITCH_DSN_MODE,
	ITM_EXITSIM,
	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};




#ifndef NULL
#define NULL 0
#endif

#endif