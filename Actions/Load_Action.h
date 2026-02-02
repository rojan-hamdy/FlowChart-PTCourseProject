#pragma once
#include "Action.h"
class Load_Action :
    public Action
{
    private:
		string filename;
        public:
        Load_Action(ApplicationManager* pAppManager);
        virtual void ReadActionParameters();
		virtual void Execute();
};

