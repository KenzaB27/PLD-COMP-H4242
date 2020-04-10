#pragma once

#include "../InstructionLine.h"
#include "../../../Expression/Expression.h"
#include "../../../../IR/IRInstr/IRInstr.h"
#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"
#include "../../../../colors.h"


class BreakCode : public InstructionLine
{
public:
    BreakCode()
    {
    }
    string getIR(BasicBlock **bb)
    {
#ifdef DEBUG
        cout << "getIR BreakCode starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
#endif
        
        if (*((*bb)->cfg->getBreakBlock()) == nullptr)
        {
            //error :  'break' statement not in loop or switch statement
            std::cerr << BOLD(FRED("ERROR :" )) << "'break' statement not in loop or switch statement. " << endl;
            exit(0);
        }
        (*bb)->setUnconditionalJump(*((*bb)->cfg->getBreakBlock()));

        return "";
    }
    virtual ~BreakCode()
    {
    }
};
