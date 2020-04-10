#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock *bb_)
{
    this->bb = bb_;
}

IRInstr::IRInstr()
{
}

string IRInstr::transParam(string par)
{
    // cout << "trans Param :" << par << endl;
    if (par == "_eax")
    {
        return "%eax";
    }
    return bb->cfg->symbolTable->IR_reg_to_asm(par);
}

void IRInstr::gen_asm(ostream &o)
{

}

IRInstr::~IRInstr()
{
}

