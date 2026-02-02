#include "Connector.h"
#include"Statements\Statement.h"
Connector::Connector(Statement* Src, Statement* Dst, int br)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	branch = br;
	SrcStat = Src;
	DstStat = Dst;
	Selected = false; //default is not selected
	Start=Point(0,0);
	End = Point(0, 0);
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	pOut->DrawConnector(Start.x, Start.y, End.x, End.y, Selected);
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}
bool Connector::IsSelected() const
{
	return Selected;
}
bool Connector::IsClicked(Point P) const
{
	const int T = 4;   // click tolerance

	int x = P.x;
	int y = P.y;

	// --------------------------------
	// LOOP CASE (destination ABOVE source)
	// --------------------------------
	if (End.y < Start.y)
	{
		int offset = 40;

		// Decide loop direction
		bool loopRight = (End.x >= Start.x);
		int dx = loopRight ? offset : -offset;

		// Segment 1: horizontal from Start to offset
		int left = min(Start.x, Start.x + dx);
		int right = max(Start.x, Start.x + dx);
		if (y >= Start.y - T && y <= Start.y + T &&
			x >= left && x <= right)
			return true;

		// Segment 2: vertical up/down
		int top = min(Start.y, End.y);
		int bottom = max(Start.y, End.y);
		if (x >= Start.x + dx - T && x <= Start.x + dx + T &&
			y >= top && y <= bottom)
			return true;

		// Segment 3: horizontal to destination
		left = min(Start.x + dx, End.x);
		right = max(Start.x + dx, End.x);
		if (y >= End.y - T && y <= End.y + T &&
			x >= left && x <= right)
			return true;

		return false;
	}

	// --------------------------------
	// NORMAL L-SHAPE CONNECTOR
	// --------------------------------
	Point mid = { End.x, Start.y };

	// Horizontal segment
	int left = min(Start.x, mid.x);
	int right = max(Start.x, mid.x);
	if (y >= Start.y - T && y <= Start.y + T &&
		x >= left && x <= right)
		return true;

	// Vertical segment
	int top = min(mid.y, End.y);
	int bottom = max(mid.y, End.y);
	if (x >= End.x - T && x <= End.x + T &&
		y >= top && y <= bottom)
		return true;

	return false;

}
void Connector::Save(ofstream& OutFile)
{
	OutFile << "CONNECTOR " << SrcStat->GetID() << " " << DstStat->GetID()<<" " << branch<< endl;
}
