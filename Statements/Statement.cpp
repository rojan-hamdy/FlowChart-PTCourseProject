#include "Statement.h"

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	static int GlobalID = 1;  // ensure unique IDs
	ID = GlobalID++;
	Text = "";
	Selected = false;
	pOutConn = nullptr;
	validated = false;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

int Statement::GetID() const
{
	return ID;
}
void Statement::setvalidated(bool i)
{
	validated = i;
}

bool Statement::isvalidated() const
{
	return validated;
}

void Statement::setGenerated(bool G)
{
	Generated = G;
}
bool Statement::getGenerated() const
{
	return Generated;
}
void Statement::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* Statement::GetConnector() const
{
	return pOutConn;
}

Connector* Statement::Simulate(Variable* vars, int& varsize, string& Error)
{
	return pOutConn;
}
