#pragma once 

#include "../InstructionLine.h"

class Assignement : public InstructionLine
{
    public:
    Assignement(){};
    virtual string getIR(BasicBlock **bb){
        return "";
    }
    virtual ~Assignement(){};
};