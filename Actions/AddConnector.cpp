#include "AddConnector.h"
#include "..\ApplicationManager.h"
#include"..\Statements\Statement.h" 
#include"..\Statements\Condition_Stat.h"
#include"..\Statements\End_Stat.h"
#include"..\Statements\Start_Stat.h"

AddConnector::AddConnector(ApplicationManager* pAppManager) :Action(pAppManager)
{
	Src = nullptr;
	Dst1 = nullptr;
    Dst2 = nullptr;
	canceled = false;
}
void AddConnector::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
    Point P;

    //Select source
    pOut->PrintMessage("Click on the SOURCE statement.");
    pIn->GetPointClicked(P);
	Src = pManager->GetStatement(P);
    if(!Src)
    {
		pOut->PrintMessage("No statement selected. Action aborted.");
        canceled = true;
        return;
    }
    //checks if end stat
    if (dynamic_cast<End_Stat*>(Src)) {
        pOut->PrintMessage("End statement can't be a source. Action aborted.");
            canceled = true;
            return;
    }
	//Check if source is conditional
    Condition_Stat* cond = dynamic_cast<Condition_Stat*>(Src);
    if (cond)
    {
		if(cond->GetYESConnector() || cond->GetNOConnector())
        {
            pOut->PrintMessage("This condition statement already has both branches connected. Action aborted.");
            canceled = true;
            return;
        }
        pOut->PrintMessage("Click on the DESTINATION statement for the YES branch.");
        pIn->GetPointClicked(P);
        Dst1 = pManager->GetStatement(P);
		if (!Dst1 || Dst1 == Src || dynamic_cast<Start_Stat*>(Dst1))
        {
            pOut->PrintMessage("Invalid YES destination. Action aborted.");
            canceled = true;
            return;
        }

        pOut->PrintMessage("Click on the DESTINATION statement for the NO branch.");
        pIn->GetPointClicked(P);
        Dst2 = pManager->GetStatement(P);
		if (Dst1 == Dst2 || !Dst2 || Dst2 == Src || dynamic_cast<Start_Stat*>(Dst2))
        {
            pOut->PrintMessage("Invalid NO destination. Action aborted.");
			canceled = true;
            return;
        }
    }
	else //Normal statement
    {
        if (Src->GetConnector()) {
            pOut->PrintMessage("This statement already has branch connected.");
                canceled = true;
            return;

        }

        pOut->PrintMessage("Click on the DESTINATION statement.");
        pIn->GetPointClicked(P);
        Dst1 = pManager->GetStatement(P);
        if (!Dst1 || Dst1 == Src || dynamic_cast<Start_Stat*>(Dst1)) {
            pOut->PrintMessage("Invalid destination. Action aborted.");
			canceled = true;
			return;
        }
	}
}
void AddConnector::Execute()
{
    ReadActionParameters();
    if (canceled)
		return;

	if (dynamic_cast<Condition_Stat*>(Src) && !Dst2)
        return;
    Condition_Stat* cond = dynamic_cast<Condition_Stat*>(Src);
    if(cond)
        {
        if(Dst1 && Dst2)
        {
            Connector* pConnYes = new Connector(Src, Dst1, 1); // YES branch
			pConnYes->setStartPoint(cond->GetOutPoint(1));
			pConnYes->setEndPoint(Dst1->GetInPoint());
            pManager->Addconnector(pConnYes);
            cond->SetYESConnector(pConnYes);

            Connector* pConnNo = new Connector(Src, Dst2, 2);  // NO branch
			pConnNo->setStartPoint(cond->GetOutPoint(2));
			pConnNo->setEndPoint(Dst2->GetInPoint());
            pManager->Addconnector(pConnNo);
            cond->SetNOConnector(pConnNo);
        }
    }
    else
    {
        if(Dst1)
        {
            Connector* pConn = new Connector(Src, Dst1, 0);
			pConn->setStartPoint(Src->GetOutPoint(0));
			pConn->setEndPoint(Dst1->GetInPoint());
            pManager->Addconnector(pConn);
            Src->SetConnector(pConn);
        }
	}
}