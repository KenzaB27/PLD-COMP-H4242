#pragma once

#include "../IRInstr.h"

class IRInstrCall : public IRInstr
{
private:
    /* data */
    string label;
    string dest; 
    vector <string> params;
    string registers[6] = {"%edi\n", "%esi\n", "%edx\n", "%ecx\n", "%r8\n", "%r9\n"};

public:
    IRInstrCall(BasicBlock *bb_, string label, string dest, vector<string> params);
    void gen_asm(ostream &o);
    ~IRInstrCall();
};
