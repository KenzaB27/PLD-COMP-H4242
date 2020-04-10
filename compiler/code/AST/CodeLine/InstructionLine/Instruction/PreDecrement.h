#pragma once

#include "Instruction.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrDecr.h"
#include "../../../../colors.h"


class PreDecrement : public Instruction
{
private:
    /* data */
    string identifier;

public:
    PreDecrement(string identifier)
    {
        this->identifier = identifier;
    }
    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR PreDecrement starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        if (!(*bb)->cfg->symbolTable->exist_in_table(identifier))
        {
            //error :  id doesn't exist in the symbol table
            std::cerr <<BOLD(FRED("ERROR :" ))<<"'"+ identifier + "' does not exist in symbols table." << endl;
            exit(0);
        }
        IRInstr *instr = new IRInstrDecr((*bb), identifier);
        (*bb)->add_IRInstr(instr);
        return identifier;
    }
    ~PreDecrement()
    {
    }
};
