#pragma once 

#include "Expression.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrInvSign.h"

class ExpressionSign : public Expression
{
private:
    /* data */
    string sign; 
    Expression * expr; 
public:
    ExpressionSign(string sign , Expression * expr);
    string getIR(BasicBlock **bb);
    Expression *getExpression();
    ~ExpressionSign();
};

