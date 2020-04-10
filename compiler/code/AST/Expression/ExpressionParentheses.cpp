#include "ExpressionParentheses.h"


ExpressionParentheses::ExpressionParentheses(Expression *expr)
{
    this->expr = expr;
}

string ExpressionParentheses::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionParentheses starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string varTempDest = expr->getIR(bb);
    return varTempDest;
}

Expression *ExpressionParentheses::getExpression()
{
    return expr;
}

ExpressionParentheses::~ExpressionParentheses()
{
    delete (expr);
}