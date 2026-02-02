#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <fstream>
#include "GUI\UI_Info.h"
#include "GUI\output.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected; //true if the connector is selected
	int branch; // to indicate which branch (for conditional statements)
public:
	Connector(Statement* Src, Statement* Dst,int br=0);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut) const;
	
	void SetSelected(bool s);
	bool IsSelected() const;
	bool IsClicked(Point P) const;
	void Save(ofstream& OutFile);
};

#endif