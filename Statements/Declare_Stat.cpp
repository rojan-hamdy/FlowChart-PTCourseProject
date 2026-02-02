#include "Declare_Stat.h"
#include <sstream>

using namespace std;

Declare_Stat::Declare_Stat(Point Lcorner, string Name)
{

	var_name = Name; //varaible name
	

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Declare_Stat::setvar_name(const string& name)
{
	var_name = name;
	UpdateStatementText();
}




void Declare_Stat::Draw(Output* pOut) const
{
	//Call Output::DrawDeclareStat function to draw declare statement 	
	pOut->DrawDeclareStat(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void Declare_Stat::UpdateStatementText()
{
	// Declare then write the variable
	ostringstream T;
	T << "Declare" << " " << var_name;
	Text = T.str();
}

bool Declare_Stat::IsClicked(Point P) const
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void Declare_Stat::Save(ofstream& OutFile)
{
	OutFile << "DECLARE" << " " <<ID<< " " << LeftCorner.x << " " << LeftCorner.y<< " " << var_name << endl;
}
void Declare_Stat::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> var_name;
	UpdateStatementText();
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	pOutConn = NULL;
}
Point Declare_Stat::GetInPoint() const
{
	return Inlet;
}
Point Declare_Stat::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* Declare_Stat::Clone(Point newPoint) const
{
	return new Declare_Stat(newPoint, var_name);
}
void Declare_Stat::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Declare_Stat::GetConnector() const
{
	return pOutConn;
}
void Declare_Stat::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Enter new variable name : ");
	var_name = pIn->GetVariable(pOut);
	UpdateStatementText();
	pOut->PrintMessage("Declare statement updated successfully.");
}
Connector* Declare_Stat::Simulate(Variable* vars, int& varsize, string& Error)	//Execute the statement in the simulation mode
{
	for (int i = 0; i < varsize; i++)
	{
		if (var_name == vars[i].getname())
		{
			Error = "Error: Two or more declared variables have the same name";
			return nullptr;
		}
	}
	vars[varsize].setvalue(0);
	vars[varsize].setname(var_name);
	vars[varsize].setinitialized(false);
	varsize++;
	return pOutConn;
}

void Declare_Stat::GenerateCode(ofstream& OutFile)
{
	
	OutFile << "double " << var_name << ";\n";
	//move to the next statement 
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
