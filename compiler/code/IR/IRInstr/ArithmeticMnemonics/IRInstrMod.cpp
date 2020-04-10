#include "IRInstrMod.h"

IRInstrMod::IRInstrMod(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrMod::gen_asm(ostream &o)
{
    o <<"    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o <<"    cltd\n";
    o <<"    idivl   " + IRInstr::transParam(op2) + "\n";
    o <<"    movl    %edx, " + IRInstr::transParam(dest) + "\n";
}

IRInstrMod::~IRInstrMod()
{
    IRInstr::~IRInstr();
}