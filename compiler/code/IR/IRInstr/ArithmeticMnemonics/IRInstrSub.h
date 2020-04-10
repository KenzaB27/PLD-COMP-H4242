#pragma once

#include "../IRInstr.h"

class IRInstr;

class IRInstrSub : public IRInstr
{
private:
    /* data */
    string x; //first param
    string y; //second param
    string dest; //destination register
public:
    IRInstrSub(BasicBlock *bb_, string x, string y, string dest);
    void gen_asm(ostream &o);
    ~IRInstrSub();
};

