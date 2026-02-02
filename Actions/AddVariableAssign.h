
#include "Action.h"
#include "..\Statements\VariableAssign.h"


class AddVariableAssign : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

	Point Position;	//Position where the user clicks to add the stat.
	
	string LHS;     // Left-hand side variable name
	string RHS;     // Right-hand side variable name
public:
	AddVariableAssign(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

