#pragma once
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrNot.h"
#include "Expression.h"


class ExpressionParentheses : public Expression
{
private:
    /* data */
    Expression *expr;

public:
    ExpressionParentheses(Expression *expr);
    string getIR(BasicBlock **bb);
    Expression *getExpression();
    ~ExpressionParentheses();
};
