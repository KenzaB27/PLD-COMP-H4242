#pragma once

#include "../IRInstr.h"

class IRInstrCopy : public IRInstr
{
private:
    /* data */
    string src; // source 
    string dest; // destination
public:
    IRInstrCopy(BasicBlock *bb_, string src, string dest);
    void gen_asm(ostream &o);
    ~IRInstrCopy();
};

