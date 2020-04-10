#pragma once

#include "Instruction.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrIncr.h"

class PostIncrement : public Instruction
{
private:
    /* data */
    string identifier;

public:
    PostIncrement(string identifier)
    {
        this->identifier = identifier;
    }
    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR PostIncrement starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        if (!(*bb)->cfg->symbolTable->exist_in_table(identifier))
        {
            //error :  id doesn't exist in the symbol table
            std::cerr <<BOLD(FRED("ERROR :" ))<<"'"+ identifier + "' does not exist in symbols table." << endl;
            exit(0);
        }
        string temp1 = (*bb)->cfg->symbolTable->create_new_tempvar();
        IRInstr *instr1 = new IRInstrRMem((*bb), identifier, temp1);
        IRInstr *instr2 = new IRInstrIncr((*bb), identifier);
        (*bb)->add_IRInstr(instr1);
        (*bb)->add_IRInstr(instr2);
        return temp1;
    }
    ~PostIncrement()
    {
    }
};
