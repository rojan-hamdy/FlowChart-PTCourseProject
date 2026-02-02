
#include "Action.h"
#include "..\Statements\Write_Stat.h"

class Write_Action : public Action
{
private:
	Point Position;
	string Var_Name;     // variable name or message
public:
	Write_Action(ApplicationManager* pAppManager);


	//Write statements position
	virtual void ReadActionParameters();

	//Create and add an write statement to the list of statements
	virtual void Execute();
};
