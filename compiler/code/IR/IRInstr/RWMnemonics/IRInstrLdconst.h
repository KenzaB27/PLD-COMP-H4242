#pragma once

#include "../IRInstr.h"

class IRInstrLdconst : public IRInstr
{
private:
    /* data */
    string dest; //destination
    string constVal; //constant
public:
    IRInstrLdconst(BasicBlock *bb_, string constVal, string dest);
    void gen_asm(ostream &o);
    ~IRInstrLdconst();
};

