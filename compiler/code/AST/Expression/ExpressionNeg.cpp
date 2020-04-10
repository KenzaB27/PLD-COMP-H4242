#include "ExpressionNeg.h"


ExpressionNeg::ExpressionNeg(Expression *expr)
{
    this->expr = expr;
}

string ExpressionNeg::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionNeg starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif
    string varTempDest = expr->getIR(bb);
    IRInstr *instr = new IRInstrNot((*bb),varTempDest);
    (*bb)->add_IRInstr(instr);

    return varTempDest;
}

Expression *ExpressionNeg::getExpression()
{
    return expr;
}

ExpressionNeg::~ExpressionNeg()
{
    delete (expr);
}