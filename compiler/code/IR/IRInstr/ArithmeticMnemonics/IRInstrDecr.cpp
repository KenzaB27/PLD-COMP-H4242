#include "IRInstrDecr.h"

IRInstrDecr::IRInstrDecr(BasicBlock *bb_, string dest) : IRInstr(bb_)
{
    this->dest = dest;
}

void IRInstrDecr::gen_asm(ostream &o)
{
    o << "    subl    $1," + IRInstr::transParam(dest) + "\n";
}

IRInstrDecr::~IRInstrDecr()
{
    IRInstr::~IRInstr();
}