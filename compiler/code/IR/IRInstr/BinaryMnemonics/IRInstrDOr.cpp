

#include "IRInstrDOr.h"

IRInstrDOr::IRInstrDOr(BasicBlock *bb_, string op1, string op2, string dest) : IRInstr(bb_)
{
    
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
}

void IRInstrDOr::gen_asm(ostream &o)
{
    o << "    cmpl    $0," + IRInstr::transParam(op1) + "\n";
    o << "    setne   %dl\n";
    o << "    cmpl    $0," + IRInstr::transParam(op2) + "\n";
    o << "    setne   %al\n";
    o << "    movzbl  %al, %eax\n";
    o << "    orl     %edx, %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";

}

IRInstrDOr::~IRInstrDOr()
{
    IRInstr::~IRInstr();
}