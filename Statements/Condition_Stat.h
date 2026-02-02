#pragma once
#include "Statement.h"

//Condition statement class

class Condition_Stat : public Statement
{
private:
	string LHS;     // Left-hand side variable name
	string comparison;      // Reads comparison operators (==, !=, <, <=, > or >=)
	string RHS;     // Right-hand side variable or value
	string type; // if or while
	Connector* pYESConn;	//Condition Stat. has one Connector to "Yes" branch
	Connector* pNOConn;	//Condition Stat. has one Connector to "No" branch

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point YesOutlet;	//A point a connection leaves this statement for "Yes" branch
	Point NoOutlet;	//A point a connection leaves this statement for "No" branch
	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Condition_Stat(Point Lcorner, string LeftHS = "",string oper = "==", string RightHS = "",string Type ="if");

	void setLHS(const string& L);
	void setRHS(const string& R);
	virtual void Draw(Output* pOut) const;
	virtual bool IsClicked(Point P) const;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual Point GetInPoint() const;
	virtual Point GetOutPoint(int branch = 0) const;
	virtual Statement* Clone(Point newPoint) const;
	void SetYESConnector(Connector* pConn);
	void SetNOConnector(Connector* pConn);
	Connector* GetYESConnector() const;
	Connector* GetNOConnector() const;
	virtual void Edit(Input* pIn, Output* pOut);
	virtual Connector* Simulate(Variable* vars, int& varsize, string& Error);	//Execute the statement in the simulation mode
	virtual void GenerateCode(ofstream& OutFile);
};