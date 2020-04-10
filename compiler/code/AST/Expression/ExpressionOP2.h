#pragma once

#include "Expression.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrAdd.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrSub.h"

class ExpressionOP2 : public Expression
{
private:
    /* data */
    string OP2;
    Expression *expr1;
    Expression *expr2;

public:
    ExpressionOP2(Expression *expr1, string OP2, Expression *expr2);
    string getIR(BasicBlock **bb);
    ~ExpressionOP2();
    Expression *getExpression();
};
