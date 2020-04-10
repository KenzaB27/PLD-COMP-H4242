#pragma once

#include "Expression.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrShift.h"


class ExpressionOPShift : public Expression
{
private:
    /* data */
    string OPShift;
    Expression *expr1;
    Expression *expr2;

public:
    ExpressionOPShift(Expression *expr1, string OPShift, Expression *expr2);
    string getIR(BasicBlock **bb);
    Expression *getExpression();
    ~ExpressionOPShift();
};
