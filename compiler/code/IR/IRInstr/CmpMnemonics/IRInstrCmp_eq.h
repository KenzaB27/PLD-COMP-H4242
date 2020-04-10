#pragma once

#include "../IRInstr.h"

class IRInstrCmp_eq : public IRInstr
{
private:
    /* data */
    string dest; 
    string op1; 
    string op2;
public:
    IRInstrCmp_eq(BasicBlock *bb_, string dest, string op1, string op2);
    void gen_asm(ostream &o);
    ~IRInstrCmp_eq();
};

