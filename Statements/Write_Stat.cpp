#include "Write_Stat.h"
#include <sstream>

using namespace std;

Write_Stat::Write_Stat(Point Lcorner, string Name)
{

	var_name = Name; //varaible name or message


	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = ((LeftCorner.x +30 + 70) + LeftCorner.x) / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = ((LeftCorner.x+ 70) +( LeftCorner.x-70)) / 2;
	Outlet.y = LeftCorner.y + 50;
}

void Write_Stat::setvar_name(const string& name)
{
	var_name = name;
	UpdateStatementText();
}

void Write_Stat::Draw(Output* pOut) const
{
	//Call Output::DrawWrite function to draw write statement 	
	pOut->DrawWrite(LeftCorner.x, LeftCorner.y, Text, Selected);

}

void Write_Stat::UpdateStatementText()
{
// Write then vatiable name or message
	ostringstream T;
	T << " " << var_name;
	Text = T.str();
}

bool Write_Stat::IsClicked(Point P) const           
{
	//Check if point P is inside the statement block
	if (P.x >= LeftCorner.x && P.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		P.y >= LeftCorner.y && P.y <= LeftCorner.y + UI.ASSGN_HI)
		return true;
	else
		return false;
}
void Write_Stat::Save(ofstream& OutFile)
{
	OutFile << "WRITE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << var_name << endl;
}
void Write_Stat::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> var_name;
	UpdateStatementText();
	Inlet.x = ((LeftCorner.x + 30 + 70) + LeftCorner.x) / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = ((LeftCorner.x + 70) + (LeftCorner.x - 70)) / 2;
	Outlet.y = LeftCorner.y + 50;
	pOutConn = NULL;
}
Point Write_Stat::GetInPoint() const
{
	return Inlet;
}
Point Write_Stat::GetOutPoint(int branch) const
{
	return Outlet;
}
Statement* Write_Stat::Clone(Point newPoint) const
{
	return new Write_Stat(newPoint, var_name);
}
void Write_Stat::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Write_Stat::GetConnector() const
{
	return pOutConn;
}
void Write_Stat::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Write Statement: Enter new variable name or message (in between quotation marks):");

	while (true)
	{
		string newVar = pIn->GetString(pOut);
		//case1 : message
		if (!newVar.empty() && newVar[0] == '\"' && newVar[newVar.size() - 1] == '\"')
		{
			var_name = newVar;
			UpdateStatementText();
			pOut->PrintMessage("Write Statement updated.");
			return;
		}
		//case2 :variable name
		if (IsVariable(newVar))
		{
			var_name = newVar;
			UpdateStatementText();
			pOut->PrintMessage("Write Statement updated.");
			return;
		}
		pOut->PrintMessage("Invalid variable name or message. Enter a valid variable or message between qoutation marks.");
	}
	
}
Connector* Write_Stat::Simulate(Variable* vars, int& varsize, string& Error, Input* pIn, Output* pOut) //Execute the statement in the simulation mode
{
	string str = "";
	if (var_name[0] == '\"' && var_name[var_name.size() - 1] == '\"')
	{
		for (int i = 1; i < var_name.size() - 1; i++)
			str += var_name[i];
	}
	else
	{
		double num1 = 0;
		bool foundandinitialized = false;
		for (int i = 0; i < varsize; i++)
		{
			if (vars[i].getname() == var_name && vars[i].isinitialized())
			{
				num1 = vars[i].getvalue();
				str = to_string(num1);
				foundandinitialized = true;
				break;
			}
		}
		if (!foundandinitialized)
		{
			Error = "Error: Undeclared or uninitialized variable in a write statement";
			return nullptr;
		}
	}
	pOut->DrawString(UI.DrawingAreaWidth + 10, UI.ToolBarHeight + 10 + UI.OutputHeightDiff, str);
	UI.OutputHeightDiff += 20;
	return pOutConn;
}
Connector* Write_Stat::validate(Variable* vars, int& varsize, string& Error)
{
	if (var_name[0] == '\"' && var_name[var_name.size() - 1] == '\"') return pOutConn;
	else
	{
		for (int i = 0; i < varsize; i++)
		{
			if (vars[i].getname() == var_name && vars[i].isinitialized())
			{
				return pOutConn;
			}
		}
	}
	Error = "Error: Undeclared or uninitialized variable in a write statement";
	return nullptr;
}

void Write_Stat::GenerateCode(ofstream& OutFile)
{
	
	OutFile << "   cout<<" << var_name << " << endl;\n";
	//move to the next statement 
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}
