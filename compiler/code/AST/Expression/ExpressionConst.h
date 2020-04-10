#pragma once
#include "../../IR/IRInstr/RWMnemonics/IRInstrLdconst.h"
#include "../../IR/IRInstr/ArithmeticMnemonics/IRInstrConstVal.h"
#include "Expression.h"


class ExpressionConst : public Expression
{
private:
    /* data */
    string value;
    string name = "";
    string nameCopie = "" ; 
    string op;
public:
    ExpressionConst(){}
    ExpressionConst(string value);
    ExpressionConst(string name, string op, string value);
    string getIR(BasicBlock **bb);
    string getValue();
    string getName();
    Expression *getExpression();
    ~ExpressionConst();
};
