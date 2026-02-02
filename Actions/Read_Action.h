
#include "Action.h"
#include "..\Statements\Read_Stat.h"

class Read_Action : public Action
{
private:
	Point Position;
	string Var_Name;     // variable name
public:
	Read_Action(ApplicationManager* pAppManager);


	//Read statements position
	virtual void ReadActionParameters();

	//Create and add an Read statement to the list of statements
	virtual void Execute();
};
