#include "ValueAssign.h"
#include <sstream>

using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

bool ValueAssign::IsClicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void ValueAssign::Save(ofstream& OutFile)
{
	OutFile << "ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << endl;
}
void ValueAssign::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	pOutConn = NULL;
}
Point ValueAssign::GetInPoint() const
{
	return Inlet;
}
Point ValueAssign::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* ValueAssign::Clone(Point newPoint) const
{
	return new ValueAssign(newPoint, LHS, RHS);
}
void ValueAssign::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* ValueAssign::GetConnector() const
{
	return pOutConn;
}
void ValueAssign::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Value Assignment Statement: Enter new LHS variable name:");
	string newLHS = pIn->GetVariable(pOut);
	LHS = newLHS;
	pOut->PrintMessage("Enter new RHS value:");
	double newRHS = pIn->GetValue(pOut);
	RHS = newRHS;
	UpdateStatementText();
	pOut->PrintMessage("Value Assignment Statement edited.");
}
Connector* ValueAssign::Simulate(Variable* vars, int& varsize, string& Error)	//Execute the statement in the simulation mode
{
	int lhsindex = 0;
	bool isfound = false;
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
		Error = "Error: undeclared variable in a value assignment statement";
		return nullptr;
	}
	vars[lhsindex].setvalue(RHS);
	vars[lhsindex].setinitialized(true);
	return pOutConn;
}

void ValueAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << "  " << LHS << "=" << RHS << ";\n";
	//move to the next statement 
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
