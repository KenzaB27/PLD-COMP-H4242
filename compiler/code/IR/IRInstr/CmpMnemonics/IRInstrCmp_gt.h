#pragma once

#include "../IRInstr.h"

class IRInstrCmp_gt : public IRInstr
{
private:
    /* data */
    string dest;
    string op1;
    string op2;
public:
    IRInstrCmp_gt(BasicBlock *bb_, string dest, string op1, string op2);
    void gen_asm(ostream &o);
    ~IRInstrCmp_gt();
};


