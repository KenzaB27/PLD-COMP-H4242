#pragma once

#include "../IRInstr.h"
/*memory write: the value of variable var is written at address addr*/
class IRInstrWMem : public IRInstr
{
private:
    /* data */
    string addr; //address
    string var;  //variable
public:
    IRInstrWMem(BasicBlock *bb_, string addr, string var);
    void gen_asm(ostream &o);
    ~IRInstrWMem();
};
