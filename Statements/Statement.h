#ifndef STATEMENT_H
#define STATEMENT_H
#include<fstream>
#include "..\defs.h"
#include "..\Connector.h"
#include "..\Variable.h"
//class Output;
#include "..\GUI\Output.h"
#include"..\GUI\Input.h"

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	Connector* pOutConn;	//Each statement has one outgoing connector (except conditional statement)
	bool Generated;
	bool validated;
	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	virtual bool IsClicked(Point P) const = 0; //check if the statement is clicked

	int GetID() const;
	virtual void setvalidated(bool i);
	virtual bool isvalidated() const;
	virtual Point GetInPoint() const = 0;		//returns the inlet point of the statement
	virtual Point GetOutPoint(int branch=0) const = 0;	//returns the outlet point of the statement
	virtual void SetConnector(Connector* pConn); //sets the outgoing connector of the statement
	virtual Connector* GetConnector() const; //returns the outgoing connector of the statement
	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(Input* pIn,Output* pOut) = 0;		//Edit the Statement parameter

	virtual Connector* Simulate(Variable* vars, int& varsize, string& Error);	//Execute the statement in the simulation mode

	 virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file [BONUS]
	 void setGenerated(bool G);
	 bool getGenerated() const;

	///TODO: Add more functions if needed
	virtual Statement* Clone(Point newPoint) const = 0; //function to print the pasted statement in the position clicked by user


};

#endif