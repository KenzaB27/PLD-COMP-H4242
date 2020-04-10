
#pragma once 

#include "../IRInstr.h"

class IRInstr;

class IRInstrConstVal : public IRInstr
{
private:
    /* data */
    string name = ""; 
    string val; 
    string op;
    string dest; //destination register
    string getAssOp(string op);

public:
    IRInstrConstVal(BasicBlock *bb_ , string name, string op, string val, string dest);
    void gen_asm(ostream &o);
    ~IRInstrConstVal();
    void optiGen_asm(ostream &o);
};

