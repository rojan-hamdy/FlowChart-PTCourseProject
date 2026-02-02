#include "Load_Action.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Input.h"
#include"..\GUI\Output.h"
#include<fstream>
#include "..\Statements\Statement.h"
#include "..\Statements\Condition_Stat.h"
#include"..\Statements\Declare_Stat.h"
#include"..\Statements\End_Stat.h"
#include"..\Statements\OperartorAssign.h"
#include"..\Statements\Read_Stat.h"
#include"..\Statements\Start_Stat.h"
#include"..\Statements\ValueAssign.h"
#include"..\Statements\VariableAssign.h"
#include"..\Statements\Write_Stat.h"



Load_Action::Load_Action(ApplicationManager* pApp) : Action(pApp)
{
}
void Load_Action::ReadActionParameters()
{
	//Get filename from user
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter filename to load: ");
	filename = pIn->GetString(pOut);
}
void Load_Action::Execute()
{
	//Read action parameters
	ReadActionParameters();
	//Open the file
	ifstream Infile;
	Infile.open(filename);
	if (!Infile)
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error: Could not open file " + filename);
		return;
	}
	//Clear the current flowchart
	pManager->clearflowchart();

	//Read statements from the file
	int StatCount;
	Infile >> StatCount;

	//Load each statement
	for (int i = 0; i < StatCount; i++)
	{
		string type;
		Infile >> type;
		Statement* pStat = nullptr;

		if (type == "START")
		{
			pStat = new Start_Stat(Point(0, 0));
		}
		else if (type == "END")
		{
			pStat = new End_Stat(Point(0, 0));
		}
		else
		if (type == "COND")
		{
			pStat = new Condition_Stat(Point(0, 0));
		}
		else if (type == "DECLARE")
		{
			pStat = new Declare_Stat(Point(0, 0));
		}
		else if (type == "OP_ASSIGN")
		{
			pStat = new OperatorAssign(Point(0, 0));
		}
		else if (type == "VARASSIGN")
		{
			pStat = new VariableAssign(Point(0, 0));
		}
		else if (type == "ASSIGN")
		{
			pStat = new ValueAssign(Point(0, 0));
		}
		else if (type == "READ")
		{
			pStat = new Read_Stat(Point(0, 0));
		}
		else if (type == "WRITE")
		{
			pStat = new Write_Stat(Point(0, 0));
		}
		pStat->Load(Infile);
		pManager->AddStatement(pStat);
	}

	//load connectors

	int connCount;
	Infile >> connCount;

	for (int i = 0; i < connCount; i++)
	{
		string CONNECTOR;
		Infile >> CONNECTOR;
		int srcID, dstID, branch;
		Infile >> srcID >> dstID >> branch;
		Statement* SrcStat = pManager->GetStatByID(srcID);
		Statement* DstStat = pManager->GetStatByID(dstID);

		if (!SrcStat || !DstStat)
			continue; //invalid IDs, skip this connector

		Connector* pConn = new Connector(SrcStat, DstStat, branch);

		pConn->setStartPoint(SrcStat->GetOutPoint(branch));
		pConn->setEndPoint(DstStat->GetInPoint());

		pManager->Addconnector(pConn);

		Condition_Stat* cond = dynamic_cast<Condition_Stat*>(SrcStat);
		if (cond) {
			if (branch == 1)
				cond->SetYESConnector(pConn);
			else if (branch == 2)
				cond->SetNOConnector(pConn);
		}
		else {
			SrcStat->SetConnector(pConn);
		}

	}

	Infile.close();
	pManager->UpdateInterface();
}
