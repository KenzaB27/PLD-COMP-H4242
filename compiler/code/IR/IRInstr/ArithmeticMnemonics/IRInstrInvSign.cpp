#include "IRInstrInvSign.h"

IRInstrInvSign::IRInstrInvSign(BasicBlock *bb_, string sign, string dest) : IRInstr(bb_)
{
    
    this->sign = sign;
    this->dest = dest;
}

void IRInstrInvSign::gen_asm(ostream &o)
{
    if (sign == "-")
    {
        o << "    negl    "+IRInstr::transParam(dest)+"\n";
    } 
}

IRInstrInvSign::~IRInstrInvSign()
{
    IRInstr::~IRInstr();
}