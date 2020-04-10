#include "IRInstrOr.h"

IRInstrOr::IRInstrOr(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrOr::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1)+ ", %eax\n";
    o << "    orl     " + IRInstr::transParam(op2)+ ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrOr::~IRInstrOr()
{
    IRInstr::~IRInstr();
}