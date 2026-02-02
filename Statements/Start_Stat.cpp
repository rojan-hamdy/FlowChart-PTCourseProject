#include "Start_Stat.h"

Start_Stat::Start_Stat(Point cent)
{
	Center = cent;
	ix = cent.x;
	iy = cent.y;
	pOutConn = NULL;	//No connectors yet
}

void Start_Stat::Draw(Output* pOut) const
{
	pOut->DrawStart(ix, iy, Selected);
}

void Start_Stat::UpdateStatementText()
{
}
bool Start_Stat::IsClicked(Point P) const
{	//Check if point P is inside the Start statement circle
	int radius = 30;
	int dx = P.x - ix;
	int dy = P.y - iy;
	if (dx * dx + dy * dy <= radius * radius)
		return true;
	else
		return false;
}
void Start_Stat::Save(ofstream& OutFile)
{
	OutFile << "START " << ID << " " << ix << " " << iy << endl;
}
void Start_Stat::Load(ifstream& Infile)
{
	Infile >> ID >> ix >> iy;
	Center.x = ix;
	Center.y = iy;
	pOutConn = NULL;
}
Point Start_Stat::GetInPoint() const
{
	return Point(-1, -1); // Start statement has no inlet
}
Point Start_Stat::GetOutPoint(int branch) const
{
	Point Out;
	Out.x = ix;
	Out.y = iy + 30;
	return Out;
}
Statement* Start_Stat::Clone(Point newPoint) const
{
	return new Start_Stat(newPoint);
}
void Start_Stat::SetConnector(Connector* pConn)
{
	pOutConn = pConn;
}
Connector* Start_Stat::GetConnector() const
{
	return pOutConn;
}
void Start_Stat::Edit(Input* pIn, Output* pOut)
{
	// Start statement has no editable parameters
}
Connector* Start_Stat::Simulate(Variable* vars, int& varsize, string& Error)
{
	return pOutConn;
}

void Start_Stat::GenerateCode(ofstream& OutFile) {
	
	// move to the next statement implementation
	if (pOutConn && pOutConn->getDstStat())
	{
		pOutConn->getDstStat()->GenerateCode(OutFile);
	}
}