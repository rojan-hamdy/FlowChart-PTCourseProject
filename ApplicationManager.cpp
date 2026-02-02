#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "Actions\AddVariableAssign.h"
#include "Actions\AddOperatorAssign.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include"Actions\SelectAction.h"
#include"Actions\Start_Action.h"
#include"Actions\End_Action.h"
#include"Actions\Declare_Action.h"
#include"Actions\Read_Action.h"
#include"Actions\Write_Action.h"
#include"Actions\AddCondition.h"
#include"Actions\AddConnector.h"
#include"Actions\Delete_StatorConn.h"
#include"Actions\Save_Action.h"
#include"Actions\Copy_Action.h"
#include"Actions\Cut_Action.h"
#include"Actions\Paste_Action.h"
#include"Actions\Edit_Action.h"
#include"Actions\Load_Action.h"
#include"Actions\Switch_To_Sim.h"
#include"Actions\Switch_To_Design.h"
#include"Actions\Validate.h"
#include"Actions/\GeneratecppAction.h"
#include"Actions/Run_Action.h"
#include"Actions/Debug.h"
#include"Variable.h"
#include"Actions/Exit.h"
//Constructor
ApplicationManager::ApplicationManager()
{

	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	pSelectedConn = NULL;	//no Connector is selected yet
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
	    case ADD_START:
		pAct = new Start_Action(this);
		break;

		case ADD_END:
			pAct = new End_Action(this);
			break;

		case ADD_DECLARE_VARIABLE:
			pAct = new Declare_Action(this);
			break;

		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;
		
		case ADD_VAR_ASSIGN:
			pAct = new AddVariableAssign(this);
			break;
		case ADD_OPER_ASSIGN:
			pAct = new AddOperatorAssign(this);
			break;

		case ADD_CONDITION:
			///create AddCondition Action here
			pAct = new AddCondition(this);
			break;

		case ADD_READ:
			pAct = new Read_Action(this);
			break;

		case ADD_WRITE:
			pAct = new Write_Action(this);
			break;

		case SELECT:
			pAct = new SelectAction(this);
			break;

		case DEL:
			pAct = new Delete_StatorConn(this);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnector(this);
			break;
		case SAVE:
			pAct = new Save_Action(this);
			break;
		case LOAD:
			pAct = new Load_Action(this);
			break;
		case COPY:
			pAct = new Copy_Action(this);
			break;
		case CUT:
			pAct = new Cut_Action(this);
			break;
		case PASTE:
			pAct = new Paste_Action(this);
			break;
		case EDIT_STAT:
			pAct = new Edit_Action(this);
			break;
		case SWITCH_SIM_MODE:
			pAct = new Switch_To_Sim(this);
			break;
		case SWITCH_DSN_MODE:
			pAct = new Switch_To_Design(this);
			break;
		case VALIDATE:
			pAct = new Validate(this);
			break;
		case RUN:
			pAct = new Run_Action(this);
			break;
		case DEBUG:
			pAct = new Debug(this);
			break;
		case GENERATE_CPP:
			pAct = new GeneratecppAction(this);
			break;

		case EXIT:
			pAct = new Exit(this);
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for (int i = 0; i < StatCount; i++)
	{
		if(StatList[i]->IsClicked(P))
			return StatList[i];
	}

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Add a connector to the list of connectors
void ApplicationManager::Addconnector(Connector *pConn)
{
	if(ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}
////////////////////////////////////////////////////////////////////////////////////
Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if(ConnList[i]->IsClicked(P))
			return ConnList[i];
	}


	return nullptr;
}


/////////////////////////////////////////////////////////////////
// Returns the selected Connector
Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}
//////////////////////////////////////////////////////////////////
//Set the Connector selected by the user
void ApplicationManager::SetSelectedConnector(Connector* pConn)
{
	pSelectedConn = pConn;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] != NULL)   // prevent null dereference
		StatList[i]->Draw(pOut);
	}
	//Draw all connections
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] != NULL)    // prevent null dereference
			ConnList[i]->Draw(pOut);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::SaveAll(ofstream& OutFile)
{
	//save number of statements
	OutFile << StatCount << endl;
	//save all statements
	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->Save(OutFile);
	}
	//save number of connectors
	OutFile << ConnCount << endl;
	//save all connectors
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(OutFile);
	}
}

void ApplicationManager::Delete_Stat(Statement* pStat)
{
	if (!pStat) return;
	
	
	//delete all connectors related to the statement 
	int i = 0;
	while (i < ConnCount)
	{  
		Connector* pConn = ConnList[i];
		if (pConn && (pConn->getSrcStat() == pStat || pConn->getDstStat() == pStat))
		{
			// Delete_Conn (delete connector from connlist and shifts the rest of the array)
			Delete_Conn(pConn);
			
		}
		else
		{
			++i;
		}
	}

	// delete the statement from the StatList
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == pStat)
		{
			// Delete the statement
			delete StatList[i];

			// Shift remaining statements
			for (int j = i; j < StatCount - 1; j++)
			{
				StatList[j] = StatList[j + 1];
			}

			// Set last position to NULL and decrement count
			
			StatList[StatCount - 1] = NULL;
			StatCount--;

			if (pSelectedStat == pStat) pSelectedStat = NULL;
			return; // action is done

		}
	}
}

void ApplicationManager::Delete_Conn(Connector* pConn)
{
	if (!pConn) return;
	Statement* src = pConn->getSrcStat();

	//delete the two Cond connectors if on is deleted
	if (Condition_Stat* cond = dynamic_cast<Condition_Stat*>(src))
	{
		Connector* yes = cond->GetYESConnector();
		Connector* no = cond->GetNOConnector();

		// clear both pointers BEFORE deleting anything
		cond->SetYESConnector(nullptr);
		cond->SetNOConnector(nullptr);

		//delete YES connector (if not the one being deleted)
		if (yes && yes != pConn)
		{
			// remove from list
			for (int i = 0; i < ConnCount; i++)
			{
				if (ConnList[i] == yes)
				{
					delete yes;

					// shift
					for (int j = i; j < ConnCount - 1; j++)
						ConnList[j] = ConnList[j + 1];

					ConnList[ConnCount - 1] = nullptr;
					ConnCount--;
					break;
				}
			}
		}

		// STEP 3 — delete NO connector (if not the one being deleted)
		if (no && no != pConn)
		{
			for (int i = 0; i < ConnCount; i++)
			{
				if (ConnList[i] == no)
				{
					delete no;

					for (int j = i; j < ConnCount - 1; j++)
						ConnList[j] = ConnList[j + 1];

					ConnList[ConnCount - 1] = nullptr;
					ConnCount--;
					break;
				}
			}
		}
	}
	//normal statement
	if (src->GetConnector() == pConn)
	{
		src->SetConnector(NULL);
	}
	
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{
			// Delete the connector
			delete ConnList[i];

			// Shift remaining connectors
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}

			// Set last position to NULL and decrement count
			ConnList[ConnCount - 1] = NULL;
			ConnCount--;
			if (pSelectedConn == pConn) pSelectedConn = NULL;
			return; // action is done
		}
	}
}

void ApplicationManager::clearflowchart()
{

	for (int i = 0; i < ConnCount; i++)
		delete ConnList[i];
	ConnCount = 0;

	for (int i = 0; i < StatCount; i++)
		delete StatList[i];
	StatCount = 0;

	pSelectedConn = NULL;
	pSelectedStat = NULL;
}

Statement* ApplicationManager::GetStatByID(int id) const
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->GetID() == id)
			return StatList[i];
	}
	return nullptr;
}

int ApplicationManager::GetStatCount() const
{
	return StatCount;
}

int ApplicationManager::GetConnCount() const
{
	return ConnCount;
}

bool ApplicationManager::validatechart()
{
	pOut->ClearOutputBar();
	UI.OutputHeightDiff = 0;
	string Errormsg;
	if (StatCount == 0)
	{
		pOut->PrintMessage("Error: Empty Flowchart"); return false;
	}

	
	int EndCount = 0;
	int StartCount = 0;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<End_Stat*>(StatList[i]))
		{
			if (EndCount == 0) EndCount++;
			else { pOut->PrintMessage("Error: More Than one End statement present in the chart"); return false; }
		}
		else if (dynamic_cast<Start_Stat*>(StatList[i]))
		{
			if (StartCount == 0) StartCount++;
			else { pOut->PrintMessage("Error: More Than one Start statement present in the chart"); return false; }
		}
		if (i == StatCount - 1 && EndCount == 0)
		{
			pOut->PrintMessage("Error: No End Statement"); return false;
		}
		if (i == StatCount - 1 && StartCount == 0)
		{
			pOut->PrintMessage("Error: No Start Statement"); return false;
		}
	}

	for (int i = 0; i < StatCount; i++)
	{
		if (Condition_Stat* pCond = dynamic_cast<Condition_Stat*>(StatList[i]))
		{
			if (pCond->GetYESConnector() == nullptr || pCond->GetNOConnector() == nullptr)
			{
				pOut->PrintMessage("Error: Some statements do not have connectors"); return false;
			}
		}
		else if (!dynamic_cast<End_Stat*>(StatList[i]) && StatList[i]->GetConnector() == nullptr)
		{
			pOut->PrintMessage("Error: Some statements do not have connectors"); return false;
		}
	}

	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->setvalidated(false);	//reset validated state in all statements to achieve reusability
	}

	Connector* pCurrentConn = nullptr;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start_Stat*>(StatList[i]))
		{
			pCurrentConn = StatList[i]->GetConnector();
		}
	}
	int varCount = 0;
	Variable vars[MaxCount];	//Composition relation, if there's no flowchart there are no variables

	while (true)
	{
		Statement* pCurrentStat = pCurrentConn->getDstStat();
		if (dynamic_cast<End_Stat*>(pCurrentStat))
		{
			pCurrentStat->setvalidated(true);
			//extra check for any non-validated statement (ex: the false branch in a conditional statement)
			for (int i = 0; i < StatCount; i++)
			{
				if (!StatList[i]->isvalidated())
				{
					if (Read_Stat* pRead = dynamic_cast<Read_Stat*>(StatList[i]))
					{
						pCurrentConn = pRead->validate(vars, varCount, Errormsg);	
						StatList[i]->setvalidated(true);
					}
					else if (Write_Stat* pWrite = dynamic_cast<Write_Stat*>(StatList[i]))
					{
						pCurrentConn = pWrite->validate(vars, varCount, Errormsg);	
						StatList[i]->setvalidated(true);
					}
					else
					{
						pCurrentConn = StatList[i]->Simulate(vars, varCount, Errormsg);
						StatList[i]->setvalidated(true);
					}
					if (!pCurrentConn)
					{
						pOut->PrintMessage(Errormsg); return false;
					}
				}
			}
			pOut->PrintMessage("Flowchart is Valid!");
			return true;
		}
		if (Read_Stat* pRead = dynamic_cast<Read_Stat*>(pCurrentStat))
		{
			pCurrentConn = pRead->validate(vars, varCount, Errormsg);	//don't ask for user input during validate
			pCurrentStat->setvalidated(true);
		}
		else if (Write_Stat* pWrite = dynamic_cast<Write_Stat*>(pCurrentStat))
		{
			pCurrentConn = pWrite->validate(vars, varCount, Errormsg);	//no output should be shown during validate
			pCurrentStat->setvalidated(true);
		}
		else if (Condition_Stat* pCond = dynamic_cast<Condition_Stat*>(pCurrentStat))	//prevent loops during validate
		{
			pCurrentConn = pCurrentStat->Simulate(vars, varCount, Errormsg);
			if (pCurrentConn != nullptr && (pCurrentConn->getDstStat())->isvalidated())
			{
				if (pCurrentConn == pCond->GetYESConnector())
				{
					pCurrentConn = pCond->GetNOConnector();
					pCurrentStat->setvalidated(true);
				}
				else
				{
					pCurrentConn = pCond->GetYESConnector();
					pCurrentStat->setvalidated(true);
				}
			}
		}
		else
		{
			pCurrentConn = pCurrentStat->Simulate(vars, varCount, Errormsg);
			pCurrentStat->setvalidated(true);
		}
		if (!pCurrentConn)
		{
			pOut->PrintMessage(Errormsg); return false;
		}
	}
}
void ApplicationManager::runchart()
{
	pOut->ClearOutputBar();
	UI.OutputHeightDiff = 0;
	string Errormsg;
	Connector* pCurrentConn = nullptr;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start_Stat*>(StatList[i]))
		{
			pCurrentConn = StatList[i]->GetConnector();
		}
	}
	int varCount = 0;
	Variable vars[MaxCount];	//Composition relation, if there's no flowchart there are no variables

	while (true)
	{
		Statement* pCurrentStat = pCurrentConn->getDstStat();
		if (dynamic_cast<End_Stat*>(pCurrentStat))
		{
			pOut->PrintMessage("Run executed Successfully!");
			return;
		}
		if (Read_Stat* pRead = dynamic_cast<Read_Stat*>(pCurrentStat))
		{
			pCurrentConn = pRead->Simulate(vars, varCount, Errormsg, pIn, pOut );	
		}
		else if (Write_Stat* pWrite = dynamic_cast<Write_Stat*>(pCurrentStat))
		{
			pCurrentConn = pWrite->Simulate(vars, varCount, Errormsg, pIn, pOut);	
		}
		else pCurrentConn = pCurrentStat->Simulate(vars, varCount, Errormsg);
		if (!pCurrentConn)
		{
			pOut->PrintMessage(Errormsg); return;
		}
	}
}
void ApplicationManager::debugchart()
{
	string Errormsg;
	Connector* pCurrentConn = nullptr;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start_Stat*>(StatList[i]))
		{
			pCurrentConn = StatList[i]->GetConnector();
		}
	}
	int varCount = 0;
	Variable vars[MaxCount];	//Composition relation, if there's no flowchart there are no variables

	string choice = ".";
	Statement* pCurrentStat = pCurrentConn->getSrcStat();
	while (true)
	{
		pOut->ClearOutputBar();
		UI.OutputHeightDiff = 0;
		pCurrentStat->SetSelected(true);
		UpdateInterface();
		if (dynamic_cast<End_Stat*>(pCurrentStat))
		{
			pOut->PrintMessage("Debug executed Successfully!");
			pCurrentStat->SetSelected(false);
			return;
		}
		if (Read_Stat* pRead = dynamic_cast<Read_Stat*>(pCurrentStat))
		{
			pCurrentConn = pRead->Simulate(vars, varCount, Errormsg, pIn, pOut);
		}
		else if (Write_Stat* pWrite = dynamic_cast<Write_Stat*>(pCurrentStat))
		{
			pCurrentConn = pWrite->Simulate(vars, varCount, Errormsg, pIn, pOut);	
		}
		else pCurrentConn = pCurrentStat->Simulate(vars, varCount, Errormsg);
		if (!pCurrentConn)
		{
			pOut->PrintMessage(Errormsg); 
			pCurrentStat->SetSelected(false);
			return;
		}

		for (int i = 0; i < varCount; i++)
		{
			string str = "Variable    ";
			str += vars[i].getname();
			if (vars[i].isinitialized())
			{
				str += "    value = ";
				str += to_string(vars[i].getvalue());
			}
			else
			{
				str += "    uninitialized";
			}

			//non-write output should be highlighted
			pOut->DrawString(UI.DrawingAreaWidth + 10, UI.ToolBarHeight + 10 + UI.OutputHeightDiff, str, LIGHTSEAGREEN);
			UI.OutputHeightDiff += 20;
		}
		pOut->PrintMessage("Highlighted Statement Executed Successfully. Press Enter to Continue or Escape to abort");
		choice = pIn->GetEnterOrEsc(pOut);
		if (choice == "esc")
		{
			pOut->PrintMessage("Debugging Aborted");
			pCurrentStat->SetSelected(false);
			pOut->ClearOutputBar();
			return;
		}
		pCurrentStat->SetSelected(false);
		pCurrentStat = pCurrentConn->getDstStat();
	}
}

// ApplicationManager.cpp
void ApplicationManager::GenerateAllCode(ofstream& OutFile) {
	// 1. Find the Start Statement
	Statement* pStart = NULL;
	for (int i = 0; i < StatCount; i++) {
		if (dynamic_cast<Start_Stat*>(StatList[i])) {
			pStart = StatList[i];
			break;
		}
	}

	if (!pStart) return;

	////2.prevents infinite loops 
	for (int i = 0; i < StatCount; i++)
	   StatList[i]->setGenerated(false);
	
	// 3. Write C++ program header
	OutFile << "#include <iostream>\n";
	OutFile << "#include <string>\n";
	OutFile << "using namespace std;\n\n";
	OutFile << "int main()\n{\n";

	// 4. Start recursive generation
	pStart->GenerateCode(OutFile);

	// 5. Close main
	OutFile << "\n    return 0;\n";
	OutFile << "}\n";
}
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i< ConnCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
