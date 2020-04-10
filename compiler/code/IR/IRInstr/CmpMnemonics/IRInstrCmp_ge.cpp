#include "IRInstrCmp_ge.h"

IRInstrCmp_ge::IRInstrCmp_ge(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrCmp_ge::gen_asm(ostream &o)
{
    o <<"    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o <<"    cmpl    " + IRInstr::transParam(op2) + ", %eax\n";
    o <<"    setge   %al\n";
    o <<"    movzbl  %al, %eax\n";
    o <<"    movl    %eax, " + IRInstr::transParam(dest) + "\n"; 
}

IRInstrCmp_ge::~IRInstrCmp_ge()
{
    IRInstr::~IRInstr();
}