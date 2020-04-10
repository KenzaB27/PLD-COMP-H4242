#pragma once

#include "Expression.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_eq.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_neq.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_ge.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_gt.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_le.h"
#include "../../IR/IRInstr/CmpMnemonics/IRInstrCmp_lt.h"
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrAnd.h"
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrDAnd.h"
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrOr.h"
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrDOr.h"
#include "../../IR/IRInstr/BinaryMnemonics/IRInstrXor.h"

class ExpressionOPBool : public Expression
{
private:
    /* data */
    string OPBool;
    Expression *expr1;
    Expression *expr2;

public:
    ExpressionOPBool(Expression *expr1, string OPBool, Expression *expr2);
    string getIR(BasicBlock **bb);
    Expression *getExpression();
    ~ExpressionOPBool();
};
