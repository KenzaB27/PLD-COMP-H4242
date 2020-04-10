#pragma once 

#include "../../../../IR/IRInstr/IRInstr.h"
#include "../InstructionLine.h"

class Instruction : public InstructionLine
{
private:
    /* data */
public:
    Instruction(/* args */){}
    virtual string getIR(BasicBlock **bb){
        return "";
    }
    virtual ~Instruction(){}
};

