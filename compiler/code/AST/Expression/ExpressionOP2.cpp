#include "ExpressionOP2.h"

ExpressionOP2::ExpressionOP2(Expression *expr1, string OP2, Expression *expr2)
{
    this->expr1 = expr1;
    this->OP2 = OP2;
    this->expr2 = expr2;
}

string ExpressionOP2::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionOP2 starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string op1 = expr1->getIR(bb);
    string op2 = expr2->getIR(bb);
    string dest = (*bb)->cfg->symbolTable->create_new_tempvar();
    IRInstr *instr; 
    
    if(OP2 == "+")
    {
        instr = new IRInstrAdd((*bb), op1, op2, dest);
    }
    else if (OP2 == "-")
    {
        instr = new IRInstrSub((*bb), op1, op2, dest);
    }

    (*bb)->add_IRInstr(instr);

    return dest;
}
Expression *ExpressionOP2::getExpression()
{
    return nullptr;
}
ExpressionOP2::~ExpressionOP2()
{
    delete (expr1);
    delete (expr2);
}