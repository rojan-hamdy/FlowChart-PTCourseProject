

#include "Statement.h"


class VariableAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
    string RHS;	//Right Handside (Value)

	Connector* pOutConn;	//Varaible Assignment Stat. has one Connector to next statement
	

	

	Point Inlet;	//A point where connections enters this statement 

	Point Outlet;	//A point a connection leaves this statement
	

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS(const string& R);

	virtual void Draw(Output* pOut) const;
	virtual bool IsClicked(Point P) const;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual Point GetInPoint() const;
	virtual Point GetOutPoint(int branch = 0) const;
	virtual Statement* Clone(Point newPoint) const;
	virtual void SetConnector(Connector* pConn);
	virtual Connector* GetConnector() const;
	virtual void Edit(Input* pIn, Output* pOut);
	virtual Connector* Simulate(Variable* vars, int& varsize, string& Error);	//Execute the statement in the simulation mode
	virtual void GenerateCode(ofstream& OutFile);
};

