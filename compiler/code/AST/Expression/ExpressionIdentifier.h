#pragma once

#include "Expression.h"


class ExpressionIdentifier : public Expression
{
private:
    /* data */
    string name;

public:
    ExpressionIdentifier(string name);
    string getIR(BasicBlock **bb);
    string getName();
    Expression *getExpression();
    ~ExpressionIdentifier();
};
