#include "IRInstrDiv.h"

IRInstrDiv::IRInstrDiv(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrDiv::gen_asm(ostream &o)
{
    o << "    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o << "    cltd\n";
    o << "    idivl   " + IRInstr::transParam(op2) + "\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";  
}

IRInstrDiv::~IRInstrDiv()
{
    IRInstr::~IRInstr();
}