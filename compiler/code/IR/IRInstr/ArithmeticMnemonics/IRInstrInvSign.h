#pragma once

#include "../IRInstr.h"

class IRInstr;

class IRInstrInvSign : public IRInstr
{
private:
    /* data */
    string sign; //sign (+ or -)
    string dest; //destination register
public:
    IRInstrInvSign(BasicBlock *bb_, string sign, string dest);
    void gen_asm(ostream &o);
    ~IRInstrInvSign();
};
