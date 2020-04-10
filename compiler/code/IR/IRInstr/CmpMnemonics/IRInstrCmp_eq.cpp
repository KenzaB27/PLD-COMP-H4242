#include "IRInstrCmp_eq.h"

IRInstrCmp_eq::IRInstrCmp_eq(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrCmp_eq::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o << "    cmpl    " + IRInstr::transParam(op2) + ", %eax\n";
    o << "    sete    %al\n";
    o << "    movzbl  %al, %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrCmp_eq::~IRInstrCmp_eq()
{
    IRInstr::~IRInstr();
}
