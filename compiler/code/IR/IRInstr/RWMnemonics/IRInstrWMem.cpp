#include "IRInstrWMem.h"

IRInstrWMem::IRInstrWMem(BasicBlock *bb_, string addr, string var) : IRInstr(bb_)
{
    
    this->addr = addr;
    this->var = var;
}

void IRInstrWMem::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(var) + ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(addr) + "\n";  
}

IRInstrWMem::~IRInstrWMem()
{
    IRInstr::~IRInstr();
}