#include "GeneratecppAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action
GeneratecppAction::GeneratecppAction(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void GeneratecppAction::ReadActionParameters()
{
	
	

}
void GeneratecppAction::Execute()
{
        Output* pOut = pManager->GetOutput();
        Input* pIn = pManager->GetInput();
       
            // 1.call validate 
            if (!pManager->validatechart())
            return;

            // 2. Ask user for filename
            pOut->PrintMessage("Enter filename to generate (without .cpp):");
            string fileName = pIn->GetString(pOut);

            ofstream OutFile(fileName + ".cpp");
            if (!OutFile.is_open()) {
                pOut->PrintMessage("Error: Could not create file.");
                return;
            }

            // 3. Start Generation
            pManager->GenerateAllCode(OutFile);

            OutFile.close();
            pOut->PrintMessage("Code generated successfully in " + fileName + ".cpp");
        
    
}
