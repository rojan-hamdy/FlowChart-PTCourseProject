#include "Read_Stat.h"
#include <sstream>

using namespace std;

Read_Stat::Read_Stat(Point Lcorner, string Name)
{

	var_name = Name; //varaible name


	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = ((LeftCorner.x + 30 + 70) + LeftCorner.x) / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = ((LeftCorner.x + 70) + (LeftCorner.x - 70)) / 2;
	Outlet.y = LeftCorner.y + 50;
}

void Read_Stat::setvar_name(const string& name)
{
	var_name = name;
	UpdateStatementText();
}

void Read_Stat::Draw(Output* pOut) const
{
	//Call Output::DrawRead function to draw read statement 	
	pOut->DrawRead(LeftCorner.x,LeftCorner.y, Text, Selected);

}

void Read_Stat::UpdateStatementText()
{
//Write then the message or the variable need to be printed 
	ostringstream T;
	T << " " << var_name;
	Text = T.str();
}

bool Read_Stat::IsClicked(Point P) const           
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void Read_Stat::Save(ofstream& OutFile)
{
	OutFile << "READ " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << var_name << endl;
}
void Read_Stat::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> var_name;
	UpdateStatementText();
	Inlet.x = ((LeftCorner.x + 30 + 70) + LeftCorner.x) / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = ((LeftCorner.x + 70) + (LeftCorner.x - 70)) / 2;
	Outlet.y = LeftCorner.y + 50;
	pOutConn = NULL;
}
Point Read_Stat::GetInPoint() const
{
	return Inlet;
}
Point Read_Stat::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* Read_Stat::Clone(Point newPoint) const
{
	return new Read_Stat(newPoint, var_name);
}
void Read_Stat::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Read_Stat::GetConnector() const
{
	return pOutConn;
}
void Read_Stat::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Read Statement: Enter new variable name:");
	string newVar = pIn->GetVariable(pOut);
	var_name = newVar;
	UpdateStatementText();
	pOut->PrintMessage("Read Statement updated.");
}
Connector* Read_Stat::Simulate(Variable* vars, int& varsize, string& Error, Input* pIn, Output* pOut)	//Execute the statement in the simulation mode
{
	int var_index = 0;
	bool isfound = false;
	for (int i = 0; i < varsize; i++)
	{
		if (var_name == vars[i].getname())
		{
			isfound = true;
			var_index = i;
			break;
		}
	}
	if (!isfound)
	{
		Error = "Error: undeclared variable in a read statement";
		return nullptr;
	}
	double val = pIn->GetValue(pOut);
	vars[var_index].setvalue(val);
	vars[var_index].setinitialized(true);
	return pOutConn;
}

Connector* Read_Stat::validate(Variable* vars, int& varsize, string& Error)
{
	int var_index = 0;
	bool isfound = false;
	for (int i = 0; i < varsize; i++)
	{
		if (var_name == vars[i].getname())
		{
			isfound = true;
			var_index = i;
			break;
		}
	}
	if (!isfound)
	{
		Error = "Error: undeclared variable in a read statement";
		return nullptr;
	}
	vars[var_index].setinitialized(true);
	return pOutConn;
}

void Read_Stat::GenerateCode(ofstream& OutFile)
{

	OutFile << "  cin>>" << var_name << ";\n";
	// Move to next statement
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
