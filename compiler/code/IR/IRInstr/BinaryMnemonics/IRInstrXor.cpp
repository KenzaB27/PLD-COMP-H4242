#include "IRInstrXor.h"

IRInstrXor::IRInstrXor(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrXor::gen_asm(ostream &o)
{
    o <<"    movl    " + IRInstr::transParam(op1)+ ", %eax\n";
    o <<"    xorl    " + IRInstr::transParam(op2)+ ", %eax\n";
    o <<"    movl    %eax, " + IRInstr::transParam(dest) + "\n";    
}

IRInstrXor::~IRInstrXor()
{
    IRInstr::~IRInstr();
}