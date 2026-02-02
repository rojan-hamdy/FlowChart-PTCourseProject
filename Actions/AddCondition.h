
#include "Action.h"
#include "..\Statements\Condition_Stat.h"


class AddCondition : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.
	string type; //to know it is if or while 
	string LHS;     // Left-hand side variable name
	string RHS;     // Right-hand side variable or value
	string comparison;      // Reads comparison operators (==, !=, <, <=, > or >=)
	

public:
	AddCondition(ApplicationManager* pAppManager);

	//Read comparison statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

