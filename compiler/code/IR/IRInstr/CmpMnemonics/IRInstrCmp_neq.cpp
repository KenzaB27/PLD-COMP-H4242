#include "IRInstrCmp_neq.h"

IRInstrCmp_neq::IRInstrCmp_neq(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrCmp_neq::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o << "    cmpl    " + IRInstr::transParam(op2) + ", %eax\n";
    o << "    setne   %al\n";
    o << "    movzbl  %al, %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrCmp_neq::~IRInstrCmp_neq()
{
    IRInstr::~IRInstr();
}
