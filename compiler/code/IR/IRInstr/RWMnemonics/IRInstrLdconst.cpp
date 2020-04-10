#include "IRInstrLdconst.h"

IRInstrLdconst::IRInstrLdconst(BasicBlock *bb_, string constVal, string dest) : IRInstr(bb_)
{
    
    this->constVal = constVal;
    this->dest = dest;
}

void IRInstrLdconst::gen_asm(ostream &o)
{
    o << "    movl    $" + constVal + ", " + IRInstr::transParam(dest) + "\n"; 
}

IRInstrLdconst::~IRInstrLdconst()
{
    IRInstr::~IRInstr();
}