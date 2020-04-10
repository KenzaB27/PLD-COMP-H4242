

#include "IRInstrAnd.h"

IRInstrAnd::IRInstrAnd(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrAnd::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1)+ ", %eax\n";
    o << "    andl    " + IRInstr::transParam(op2)+ ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n"; 
}

IRInstrAnd::~IRInstrAnd()
{
    IRInstr::~IRInstr();
}