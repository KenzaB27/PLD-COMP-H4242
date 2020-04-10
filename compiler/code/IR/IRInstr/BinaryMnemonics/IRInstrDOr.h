#pragma once

#include "../IRInstr.h"

class IRInstrDOr : public IRInstr
{
private:
    /* data */
    string op1; //first param
    string op2; //second param
    string dest; //destination register
public:
    IRInstrDOr(BasicBlock *bb_, string op1, string op2, string dest);
    void gen_asm(ostream &o);
    ~IRInstrDOr();
};
