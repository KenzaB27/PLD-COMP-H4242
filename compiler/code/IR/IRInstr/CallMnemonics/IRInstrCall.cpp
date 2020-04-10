
#include "IRInstrCall.h"

IRInstrCall::IRInstrCall(BasicBlock *bb_, string label, string dest, vector<string> params) : IRInstr(bb_)
{
    
    this->label = label;
    this->dest = dest;
    this->params = params;
}

void IRInstrCall::gen_asm(ostream &o)
{
    for (int i = 0; i<params.size() ; i++)
    {
        o << "    movl    " + IRInstr::transParam(params[i]) + ", " + registers[i];
    }
    o << "    call    " + label + "\n";
}

IRInstrCall::~IRInstrCall()
{
    IRInstr::~IRInstr();
}
