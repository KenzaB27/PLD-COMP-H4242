#include "IRInstrMul.h"

IRInstrMul::IRInstrMul(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrMul::gen_asm(ostream &o)
{
    o <<"    movl    " + IRInstr::transParam(op1)+ ", %eax\n";
    o <<"    imull   " + IRInstr::transParam(op2)+ ", %eax\n";
    o <<"    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrMul::~IRInstrMul()
{
    IRInstr::~IRInstr();
}