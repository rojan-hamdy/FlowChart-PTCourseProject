#include "Condition_Stat.h"
#include <sstream>

using namespace std;

Condition_Stat::Condition_Stat(Point Lcorner, string LeftHS, string oper, string RightHS,string Type)
{
	
	LHS = LeftHS;
	comparison = oper;
	RHS = RightHS;
	type = Type;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pYESConn = NULL;	//No connectors yet
	pNOConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x;
	Inlet.y = LeftCorner.y;

	YesOutlet.x = LeftCorner.x - 50;
	YesOutlet.y = LeftCorner.y + 45;

	NoOutlet.x = LeftCorner.x + 50;
	NoOutlet.y = LeftCorner.y + 45;
	
}

void Condition_Stat::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void Condition_Stat::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}




void Condition_Stat::Draw(Output* pOut) const
{
	//Call Output::DrawCondtionalStat function to draw condition statement 	
	pOut->DrawCondtionalStat(LeftCorner.x, LeftCorner.y,Text, Selected);

}


//This function should be called when LHS or RHS changes
void Condition_Stat::UpdateStatementText()
{
	//Build the condition text: Left handside then Comparison Operator then right handside
	ostringstream T;
	T <<type<<" "<< LHS << comparison << RHS;
	Text = T.str();
}
bool Condition_Stat::IsClicked(Point P) const
{
	//Check if point P is inside the statement block
	// Diamond parameters used in drawing
	int xCenter = LeftCorner.x;
	int yTop = LeftCorner.y;

	int xDiff = 50;
	int yDiff = 90;

	int halfY = yDiff / 2;

	// Diamond center
	int cx = xCenter;
	int cy = yTop + halfY;

	// Convert diamond to equation of |x - cx| / xDiff + |y - cy| / halfY <= 1
	double dx = abs(P.x - cx) / double(xDiff);
	double dy = abs(P.y - cy) / double(halfY);

	if (dx + dy <= 1.0)
		return true;
	else
		return false;
}
void Condition_Stat::Save(ofstream& OutFile)
{
	OutFile << "COND " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " "
		<< LHS << " " << comparison << " " << RHS << endl;
}
void Condition_Stat::Load(ifstream& Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> comparison >> RHS;
	UpdateStatementText();
	Inlet.x = LeftCorner.x;
	Inlet.y = LeftCorner.y;
	YesOutlet.x = LeftCorner.x - 50;
	YesOutlet.y = LeftCorner.y + 45;
	NoOutlet.x = LeftCorner.x + 50;
	NoOutlet.y = LeftCorner.y + 45;
	pYESConn = NULL;
	pNOConn = NULL;
}
Point Condition_Stat::GetInPoint() const
{
	return Inlet;
}
Point Condition_Stat::GetOutPoint(int branch) const
{
	if (branch == 1) //yes branch
		return YesOutlet;
	else if (branch == 2) //No branch
		return NoOutlet;
	else
		return Point(-1, -1); //invalid branch
}
Statement* Condition_Stat::Clone(Point newPoint) const
{
	return new Condition_Stat(newPoint, LHS, comparison, RHS);
}
void Condition_Stat::SetYESConnector(Connector* pConn)
{
	pYESConn = pConn;
}
void Condition_Stat::SetNOConnector(Connector* pConn)
{
	pNOConn = pConn;
}
Connector* Condition_Stat::GetYESConnector() const
{
	return pYESConn;
}
Connector* Condition_Stat::GetNOConnector() const
{
	return pNOConn;
}
void Condition_Stat::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Enter new LHS variable:");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Enter new Comparison Operator (==, !=, <, <=, >, >=):");
	comparison = pIn->GetCompOperator(pOut);
	pOut->PrintMessage("Enter new RHS variable or value:");
	RHS= pIn->GetVarorVal(pOut);
	UpdateStatementText();
	pOut->PrintMessage("Condition Statement updated.");
}
Connector* Condition_Stat::Simulate(Variable* vars, int& varsize, string& Error)	//Execute the statement in the simulation mode)
{
	int num1, num2;
	int lhs_index = 0, rhs_index = 0;
	bool isfound1 = false, isfound2 = false;
	for (int i = 0; i < varsize; i++)
	{
		if (vars[i].getname() == LHS && vars[i].isinitialized())
		{
			lhs_index = i;
			isfound1 = true;
			break;
		}
	}
	if (!isfound1)
	{
		Error = "Error: left hand side variable in a conditional statement is undeclared/uninitialized";
		return nullptr;
	}
	num1 = vars[lhs_index].getvalue();
	if (IsValue(RHS))
	{
		num2 = string_to_double(RHS);
	}
	else if (IsVariable(RHS))
	{
		for (int i = 0; i < varsize; i++)
		{
			if (vars[i].getname() == RHS && vars[i].isinitialized())
			{
				rhs_index = i;
				isfound2 = true;
				break;
			}
		}
		if (!isfound2)
		{
			Error = "Error: right hand side variable in a conditional statement is undeclared/uninitialized";
			return nullptr;
		}
		num2 = vars[rhs_index].getvalue();
	}
	//==, !=, <, <=, >, >=
	if (comparison == "==")
	{
		if (num1 == num2)
			return pYESConn;
		else return pNOConn;
	}
	else if (comparison == "!=")
	{
		if (num1 != num2)
			return pYESConn;
		else return pNOConn;
	}
	else if (comparison == "<")
	{
		if (num1 < num2)
			return pYESConn;
		else return pNOConn;
	}
	else if (comparison == "<=")
	{
		if (num1 <= num2)
			return pYESConn;
		else return pNOConn;
	}
	else if (comparison == ">")
	{
		if (num1 > num2)
			return pYESConn;
		else return pNOConn;
	}
	else if (comparison == ">=")
	{
		if (num1 >= num2)
			return pYESConn;
		else return pNOConn;
	}
}

void Condition_Stat::GenerateCode(ofstream& OutFile)
{
	//prevent the crash
	if (this->getGenerated()) {
		return;
	}
	this->setGenerated(true);
	if (type == "if")
	{
		// 1. Write the IF condition
		OutFile << "    if (" << LHS << " " << comparison << " " << RHS << ") \n";
		OutFile << "    {\n";

		// 2. Generate code for the "YES" branch
		if (pYESConn && pYESConn->getDstStat())
		{
			//Declare the statement type and apply the corresponding code 
			pYESConn->getDstStat()->GenerateCode(OutFile);
		}

		OutFile << "    }\n";
		OutFile << "    else \n";
		OutFile << "    {\n";

		// 3. Generate code for the "NO" branch
		if (pNOConn && pNOConn->getDstStat())
		{
			pNOConn->getDstStat()->GenerateCode(OutFile);

		}

		OutFile << "    }\n";
	}
	else if(type== "while")
	{

		// 1. Write the IF condition
		OutFile << "    while (" << LHS << " " << comparison << " " << RHS << ") \n";
		OutFile << "    {\n";

		// 2. Generate code for the "YES" branch
		if (pYESConn && pYESConn->getDstStat())
		{
			//Declare the statement type and apply the corresponding code 
			pYESConn->getDstStat()->GenerateCode(OutFile);
		}

		OutFile << "    }\n";
		

		// 3. Generate code for the "NO" branch
		if (pNOConn && pNOConn->getDstStat())
		{
			pNOConn->getDstStat()->GenerateCode(OutFile);

		}
	}
	
}
