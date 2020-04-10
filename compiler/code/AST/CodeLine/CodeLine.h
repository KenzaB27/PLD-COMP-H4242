#pragma once 

#include "../../IR/BasicBlock.h"

class BasicBlock;

class CodeLine
{
public:
    CodeLine() {};
    virtual ~CodeLine() {};
    virtual string getIR(BasicBlock **bb)
    {
        return "";
    }
};
