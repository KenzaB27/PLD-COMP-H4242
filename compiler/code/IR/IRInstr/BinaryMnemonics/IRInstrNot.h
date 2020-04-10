#pragma once

#include "../IRInstr.h"

class IRInstrNot : public IRInstr
{
private:
    /* data */
    string dest; //destination register
public:
    IRInstrNot(BasicBlock *bb_, string dest);
    void gen_asm(ostream &o);
    ~IRInstrNot();
};
