
#include "Action.h"
#include "..\Statements\OperartorAssign.h"


class AddOperatorAssign : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.
	
	string LHS;     // Left-hand side variable name
	string firstoper;     //first operand in the operation
	string operation;      // Arithmetic operators(+,/,*,-)
	string secondoper;     //second operand in the operation

public:
	AddOperatorAssign(ApplicationManager* pAppManager);

	//Read operator Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

