#pragma once

#include "../IRInstr.h"
/*memory read: the content of address addr is copied in variable dest*/
class IRInstrRMem : public IRInstr
{
private:
    /* data */
    string dest; //destination
    string addr; //adsress
public:
    IRInstrRMem(BasicBlock *bb_, string addr, string dest);
    void gen_asm(ostream &o);
    ~IRInstrRMem();
};

