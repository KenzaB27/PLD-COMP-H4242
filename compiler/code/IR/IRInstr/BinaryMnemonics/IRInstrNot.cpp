#include "IRInstrNot.h"

IRInstrNot::IRInstrNot(BasicBlock *bb_, string dest) : IRInstr(bb_)
{
    
    this->dest = dest;
}

void IRInstrNot::gen_asm(ostream &o)
{
    string ass = "    xorl    "+IRInstr::transParam(dest)+"\n";
}

IRInstrNot::~IRInstrNot()
{
    IRInstr::~IRInstr();
}