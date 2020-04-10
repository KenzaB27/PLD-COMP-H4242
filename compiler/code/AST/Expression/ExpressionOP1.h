#pragma once

#include "Expression.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrMul.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrDiv.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrMod.h"

class ExpressionOP1 : public Expression
{
private:
    /* data */
    string OP1;
    Expression *expr1;
    Expression *expr2;

public:
    ExpressionOP1(Expression *expr1, string OP1, Expression *expr2);
    string getIR(BasicBlock **bb);
    ~ExpressionOP1();
    Expression *getExpression();
};
