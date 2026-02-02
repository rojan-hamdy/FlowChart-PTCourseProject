#include "Switch_To_Sim.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"

Switch_To_Sim:: Switch_To_Sim(ApplicationManager* pAppManager) : Action(pAppManager) {}
void Switch_To_Sim::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Switch To Simulation Mode.");
	pOut->CreateSimulationToolBar();
}
void Switch_To_Sim::Execute()
{
	UI.AppMode = SIMULATION;
	ReadActionParameters();
}
