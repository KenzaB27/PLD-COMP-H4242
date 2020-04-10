
#include "IRInstrAdd.h"

IRInstrAdd::IRInstrAdd(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrAdd::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1) + ", %edx\n";
    o << "    movl    " + IRInstr::transParam(op2) + ", %eax\n";
    o << "    addl    %edx, %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrAdd::~IRInstrAdd()
{
    IRInstr::~IRInstr();
}
