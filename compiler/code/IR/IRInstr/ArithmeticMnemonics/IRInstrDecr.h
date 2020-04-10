#pragma once

#include "../IRInstr.h"

class IRInstr;

class IRInstrDecr : public IRInstr
{
private:
    string dest; //destination register
public:
    IRInstrDecr(BasicBlock *bb_, string dest);
    void gen_asm(ostream &o);
    ~IRInstrDecr();
};
