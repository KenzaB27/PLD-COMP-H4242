
#include "IRInstrConstVal.h"
#include <math.h>

IRInstrConstVal::IRInstrConstVal(BasicBlock *bb_, string name, string op, string val, string dest) : IRInstr(bb_)
{
    this->name = name;
    this->val = val;
    this->op = op;
    this->dest = dest;
}
string IRInstrConstVal::getAssOp(string op)
{
    if (op == "+")
    {
        return "addl";
    }
    else if (op.find("-") != string::npos)
    {
        return "subl";
    }
    else if (op == "*")
    {
        return "imull";
    }
    return "";
}

void IRInstrConstVal::gen_asm(ostream &o)
{
    if (name == "")
    {
        o << "    movl    $" << val << ", " << IRInstr::transParam(dest) << endl;
    }
    else
    {
        o << "    movl    " << IRInstr::transParam(name) << ", %eax" << endl;
        
        if (op=="*")
        {
            optiGen_asm(o);
        }
        else{
            o << "    " << getAssOp(op) << "    $" << val << ", %eax" << endl;
            if (op == "--")
            {
                o << "    negl    %eax" << endl;
            }
        }

        o << "    movl    %eax, " << IRInstr::transParam(dest) << endl;
    }
}

void IRInstrConstVal::optiGen_asm(ostream &o)
{
    int value = stoi(val);
    int valTemp = ((value % 2 == 0)) ? value : value - 1;
    /** verifies if the const with wich we are multiplying the var is a power of 2 
     so that we can do a left shift to opmtimize the multiplication **/
    if (valTemp && !(valTemp & (valTemp - 1)))
    {
        int pow = log2(valTemp);
        /** if the val is a multiple of 2 we only need to shift **/
        if (value == valTemp)
        {
            o << "    sall    $" + to_string(pow) + ", %eax\n";
        }
        /** if not we copy the contente of the register in edx before shifting so that 
         we cann add the var to multiply one last time **/
        else
        {
            o << "    movl    " << IRInstr::transParam(name) << ", %edx" << endl;
            o << "    movl    %edx, %eax" << endl ;
            o << "    sall    $" + to_string(pow) + ", %eax" <<endl;
            o << "    addl    %edx, %eax" << endl;
        }
    }
    else
    {
        o <<"    imull   $" << val << ", %eax, %eax" << endl;
    }
}

IRInstrConstVal::~IRInstrConstVal()
{
    IRInstr::~IRInstr();
}

