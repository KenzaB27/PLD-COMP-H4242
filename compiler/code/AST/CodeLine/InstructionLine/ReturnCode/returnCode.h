#pragma once 

#include "../InstructionLine.h"
#include "../../../Expression/Expression.h"
#include "../../../../IR/IRInstr/IRInstr.h"
#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"

class ReturnCode : public InstructionLine
{
private:
    Expression * expression;
public:
    ReturnCode(Expression *expression) {
        this->expression = expression;
    }
    string getIR(BasicBlock **bb){
        #ifdef DEBUG
        cout << "getIR ReturnCode starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        string addr = expression->getIR(bb);
        // cout << "DEBUG ReturnCode " << addr << endl ;
        IRInstr *instr1 = new IRInstrRMem((*bb), addr, "_retvalue");
        (*bb)->add_IRInstr(instr1);

        if((*bb)->cfg->getReturnBlock()->instrs.size()==0)
        {
            IRInstr *instr2 = new IRInstrRMem((*bb), "_retvalue", "_eax");
            (*bb)->cfg->getReturnBlock()->add_IRInstr(instr2);
        }
        
        (*bb)->cfg->getReturnBlock()->setUnconditionalJump((*bb)->getUnconditionalJump());

        (*bb)->setUnconditionalJump((*bb)->cfg->getReturnBlock());

        return "";
    }
    virtual ~ReturnCode()
    {
        delete(expression);
    }
};

