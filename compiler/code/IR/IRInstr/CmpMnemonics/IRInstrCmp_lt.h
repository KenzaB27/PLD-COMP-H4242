#pragma once

#include "../IRInstr.h"

class IRInstrCmp_lt : public IRInstr
{
private:
    /* data */
    string dest;
    string op1;
    string op2;
public:
    IRInstrCmp_lt(BasicBlock *bb_, string dest, string op1, string op2);
    void gen_asm(ostream &o);
    ~IRInstrCmp_lt();
};


