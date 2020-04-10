#include "IRInstrRMem.h"

IRInstrRMem::IRInstrRMem(BasicBlock *bb_, string addr, string dest) : IRInstr(bb_)
{
    this->addr = addr;
    this->dest = dest;
}

void IRInstrRMem::gen_asm(ostream &o)
{
    // cout << "DEBUG IRInstrRMem " << endl;
    // cout << IRInstr::transParam(dest)  << ": "<< dest << endl;
    o << "    movl    " + IRInstr::transParam(addr) + ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrRMem::~IRInstrRMem()
{
    IRInstr::~IRInstr();
}