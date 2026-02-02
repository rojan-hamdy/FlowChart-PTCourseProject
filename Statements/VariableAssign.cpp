#include "VariableAssign.h"
#include <sstream>

using namespace std;

VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VariableAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}


void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void VariableAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}
bool VariableAssign::IsClicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void VariableAssign::Save(ofstream& OutFile)
{
	OutFile << "VARASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}
void VariableAssign::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	pOutConn = NULL;
}
Point VariableAssign::GetInPoint() const
{
	return Inlet;
}
Point VariableAssign::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* VariableAssign::Clone(Point newPoint) const
{
	return new VariableAssign(newPoint, LHS, RHS);
}
void VariableAssign::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* VariableAssign::GetConnector() const
{
	return pOutConn;
}
void VariableAssign::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Variable Assignment Statement. Enter new LHS variable: ");
	string newLHS = pIn->GetVariable(pOut);
	LHS = newLHS;
	pOut->PrintMessage("Enter new RHS variable: ");
	string newRHS = pIn->GetVariable(pOut);
	RHS = newRHS;
	UpdateStatementText();
	pOut->PrintMessage("Variable Assignment Statement updated.");
}
Connector* VariableAssign::Simulate(Variable* vars, int& varsize, string& Error)	//Execute the statement in the simulation mode
{
	int lhsindex = 0, rhsindex = 0;
	bool lhsfound = false, rhsfound = false;
	for (int i = 0; i < varsize; i++)
	{
		if (LHS == vars[i].getname())
		{
			lhsfound = true;
			lhsindex = i;
		}
		if (RHS == vars[i].getname() && vars[i].isinitialized())
		{
			rhsfound = true;
			rhsindex = i;
		}
		if (lhsfound && rhsfound)
		{
			break;
		}
	}
	if (!lhsfound || !rhsfound)
	{
		Error = "Error: undeclared or uninitialized variable/s in a variable assignment statement";
		return nullptr;
	}
	vars[lhsindex].setvalue(vars[rhsindex].getvalue());
	vars[lhsindex].setinitialized(true);
	return pOutConn;
}

void VariableAssign::GenerateCode(ofstream& OutFile)
{
	
	OutFile << "  " << LHS << "=" << RHS << ";\n";
	//move to the next statement 
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
