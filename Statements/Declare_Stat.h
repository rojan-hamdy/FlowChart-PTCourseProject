

#include "Statement.h"


class Declare_Stat : public Statement
{
private:
	string var_name;	//name of the variable
	

	Connector* pOutConn;	//Declare value Assignment Stat. has one Connector to next statement
	

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Declare_Stat(Point Lcorner, string Name = "");

	void setvar_name(const string& name);
	

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

