#include "IRInstrCopy.h"

IRInstrCopy::IRInstrCopy(BasicBlock *bb_, string src, string dest) : IRInstr(bb_)
{
    
    this->src = src;
    this->dest = dest;
}

void IRInstrCopy::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(src) + ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
 
}

IRInstrCopy::~IRInstrCopy()
{
    IRInstr::~IRInstr();
}