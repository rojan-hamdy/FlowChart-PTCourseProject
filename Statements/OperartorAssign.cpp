#include "OperartorAssign.h"
#include <sstream>

using namespace std;

OperatorAssign::OperatorAssign(Point Lcorner, string LeftHS , string First , string oper , string second )
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	 firstoper = First;    
	 operation=oper;     
	 secondoper=second;     


	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OperatorAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}




void OperatorAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void OperatorAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << firstoper  << operation << secondoper;
	Text = T.str();
}
bool OperatorAssign::IsClicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void OperatorAssign::Save(ofstream& OutFile)
{
	OutFile << "OP_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << firstoper << " " << operation << " " << secondoper << endl;
}
void OperatorAssign::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> firstoper >> operation >> secondoper;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	pOutConn = NULL;
}
Point OperatorAssign::GetInPoint() const
{
	return Inlet;
}
Point OperatorAssign::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* OperatorAssign::Clone(Point newPoint) const
{
	return new OperatorAssign(newPoint, LHS, firstoper, operation, secondoper);
}
void OperatorAssign::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* OperatorAssign::GetConnector() const
{
	return pOutConn;
}
void OperatorAssign::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Operator Assignment Statement: Enter new LHS variable name:");
	string newLHS = pIn->GetVariable(pOut);
	setLHS(newLHS);
	pOut->PrintMessage("Editing Operator Assignment Statement: Enter first operand:");
	string newFirst = pIn->GetVarorVal(pOut);
	firstoper = newFirst;
	pOut->PrintMessage("Editing Operator Assignment Statement: Enter operation (+, -, *, /):");
	string newOper = pIn->GetArithOperator(pOut);
	operation = newOper;
	pOut->PrintMessage("Editing Operator Assignment Statement: Enter second operand:");
	string newSecond = pIn->GetVarorVal(pOut);
	secondoper = newSecond;
	UpdateStatementText();
	pOut->ClearStatusBar();
}
Connector* OperatorAssign:: Simulate(Variable* vars, int& varsize, string& Error)	//Execute the statement in the simulation mode
{
	bool isfound = false;
	int lhsindex = 0;
	for (int i = 0; i < varsize; i++)
	{
		if (LHS == vars[i].getname())
		{
			isfound = true;
			lhsindex = i;
			break;
		}
	}
	if (!isfound)
	{
		Error = "Error: Left hand side variable is undeclared in an operator assignment statement";
		return nullptr;
	}
	double num1, num2;
	if (IsVariable(firstoper))
	{
		bool foundandinitialized = false;
		for (int i = 0; i < varsize; i++)
		{
			if (vars[i].getname() == firstoper && vars[i].isinitialized())
			{
				num1 = vars[i].getvalue();
				foundandinitialized = true;
				break;
			}
		}
		if (!foundandinitialized)
		{
			Error = "Error: Some variables are undeclared or uninitialized in an operator assignment statement";
			return nullptr;
		}
	}
	else if (IsValue(firstoper))
	{
		num1 = string_to_double(firstoper);
	}
	else
	{
		Error = "Error: Operator assignment statement holds neither a variable nor a value";
	}

	if (IsVariable(secondoper))
	{
		bool foundandinitialized = false;
		for (int i = 0; i < varsize; i++)
		{
			if (vars[i].getname() == secondoper && vars[i].isinitialized())
			{
				num2 = vars[i].getvalue();
				foundandinitialized = true;
				break;
			}
		}
		if (!foundandinitialized)
		{
			Error = "Error: Some variables are undeclared or uninitialized in an operator assignment statement";
			return nullptr;
		}
	}
	else if (IsValue(secondoper))
	{
		num2 = string_to_double(secondoper);
	}
	else
	{
		Error = "Error: Operator assignment statement holds neither a variable nor a value";
	}

	if (operation == "+")
		vars[lhsindex].setvalue(num1 + num2);
	else if (operation == "-")
		vars[lhsindex].setvalue(num1 - num2);
	else if (operation == "*")
		vars[lhsindex].setvalue(num1 * num2);
	else if (operation == "/")
	{
		if (num2 == 0)
		{
			Error = "Error: Division by zero in an operator assignment statement";
			return nullptr;
		}
		vars[lhsindex].setvalue(num1 / num2);
	}
	vars[lhsindex].setinitialized(true);
	return pOutConn;
}

void OperatorAssign::GenerateCode(ofstream& OutFile)
{
	
	OutFile << " " << LHS << " = " << firstoper << operation << secondoper <<";\n";
	//move to the next statement 
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
