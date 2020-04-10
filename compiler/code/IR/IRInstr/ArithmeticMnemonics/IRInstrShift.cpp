
#include "IRInstrShift.h"

IRInstrShift::IRInstrShift(BasicBlock *bb_, string op1, string op2, string dest, bool right) : IRInstr(bb_)
{
    this->op1 = op1;
    this->op2 = op2;
    this->dest = dest;
    this->right = right;
}

void IRInstrShift::gen_asm(ostream &o)
{
    string shiftOp = (right)?"sarl":"sall";
    o << "    movl    " + IRInstr::transParam(op2) + ", %eax\n";
    o << "    movl    %eax, %edx\n";
    o << "    movl    " + IRInstr::transParam(op1) + ", %eax\n";
    o << "    movl    %edx, %ecx\n";
    o << "    " + shiftOp + "    %cl, %eax\n";
    o << "    movl    %eax, " + IRInstr::transParam(dest) + "\n";
}

IRInstrShift::~IRInstrShift()
{
    IRInstr::~IRInstr();
}
