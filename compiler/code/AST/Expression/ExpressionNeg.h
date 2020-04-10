#pragma once
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrNot.h"
#include "Expression.h"


class ExpressionNeg : public Expression
{
private:
    /* data */
    Expression *expr;

public:
    ExpressionNeg(Expression *expr);
    string getIR(BasicBlock **bb);
    ~ExpressionNeg();
    Expression *getExpression();
};
