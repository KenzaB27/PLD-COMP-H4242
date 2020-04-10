#include "IRInstrIncr.h"

IRInstrIncr::IRInstrIncr(BasicBlock *bb_, string dest) : IRInstr(bb_)
{
    this->dest = dest;
}

void IRInstrIncr::gen_asm(ostream &o)
{
    o << "    addl    $1," + IRInstr::transParam(dest) + "\n";
}

IRInstrIncr::~IRInstrIncr()
{
    IRInstr::~IRInstr();
}