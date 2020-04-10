#include "IRInstrSub.h"

IRInstrSub::IRInstrSub(BasicBlock *bb_, string x, string y, string dest) : IRInstr(bb_)
{
    
    this->x = x;
    this->y = y;
    this->dest = dest;
}

void IRInstrSub::gen_asm(ostream &o)
{
    

    o << "    movl    " + IRInstr::transParam(x) + ", %eax\n";
    o << "    subl    " + IRInstr::transParam(y) + ", %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";

    
}

IRInstrSub::~IRInstrSub()
{
    IRInstr::~IRInstr();
}