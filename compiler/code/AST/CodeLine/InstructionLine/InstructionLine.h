#pragma once

#include "../../../IR/BasicBlock.h"
#include "../CodeLine.h"

class InstructionLine : public CodeLine
{
private:
    /* data */
public:
    InstructionLine(/* args */)
    {
    }
    virtual string getIR(BasicBlock **bb){
        return "";
    }
    virtual ~InstructionLine()
    {
    }
};

