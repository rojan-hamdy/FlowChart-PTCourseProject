#pragma once
#include "Statement.h"
class Start_Stat : public Statement
{
private:
	Connector* pOutConn;
	int ix, iy;
	Point Center;	//center of the start statement.

	virtual void UpdateStatementText();     // Start has no text
public:
	Start_Stat(Point cent);
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
	virtual Connector* Simulate(Variable* vars, int& varsize, string& Error);
	virtual void GenerateCode(ofstream& OutFile);
};

