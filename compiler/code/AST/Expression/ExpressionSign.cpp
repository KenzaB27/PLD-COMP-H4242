#include "ExpressionSign.h"


ExpressionSign::ExpressionSign(string sign, Expression *expr){
    this->sign = sign ; 
    this->expr = expr; 
}

string ExpressionSign::getIR(BasicBlock **bb){
    #ifdef DEBUG
        cout << "getIR ExpressionSign starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string varTempDest = expr->getIR(bb);
    IRInstr *instr = new IRInstrInvSign((*bb), sign, varTempDest);
    (*bb)->add_IRInstr(instr);

    return varTempDest;
}

Expression *ExpressionSign::getExpression()
{
    return expr;
}

ExpressionSign::~ExpressionSign()
{
    delete(expr);
}