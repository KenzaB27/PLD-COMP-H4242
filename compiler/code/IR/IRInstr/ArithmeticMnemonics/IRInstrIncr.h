#pragma once

#include "../IRInstr.h"

class IRInstr;

class IRInstrIncr : public IRInstr
{
private:
    string dest; //destination register
public:
    IRInstrIncr(BasicBlock *bb_, string dest);
    void gen_asm(ostream &o);
    ~IRInstrIncr();
};
