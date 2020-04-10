
#pragma once 

#include "../IRInstr.h"

class IRInstr;

class IRInstrShift : public IRInstr
{
private:
    /* data */
    string op1; //first param
    string op2; //second param
    string dest; //destination register
    bool right;

public:
    IRInstrShift(BasicBlock *bb_ , string op1, string op2, string dest, bool right);
    void gen_asm(ostream &o);
    ~IRInstrShift();
};

