#pragma once 

#include <string>
using namespace std;
#include "../../IR/BasicBlock.h"

class BasicBlock;

class Expression
{
protected:
    /* data */
    string dest; //destination register
public:
    Expression();
    virtual ~Expression();
    virtual string getIR(BasicBlock **bb);
    virtual Expression *getExpression();
};
