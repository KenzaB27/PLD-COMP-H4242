#include "ExpressionOP1.h"

ExpressionOP1::ExpressionOP1(Expression *expr1, string OP1, Expression *expr2)
{
    this->expr1 = expr1;
    this->OP1 = OP1;
    this->expr2 = expr2;
}

string ExpressionOP1::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionOP1 starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string op1 = expr1->getIR(bb);
    string op2 = expr2->getIR(bb);
    string dest = (*bb)->cfg->symbolTable->create_new_tempvar();
    

    IRInstr *instr; 
    if(OP1 == "*")
    {
        instr = new IRInstrMul((*bb), op1, op2, dest);
    }
    else if (OP1 == "/")
    {
        instr = new IRInstrDiv((*bb), op1, op2, dest);
    }
    else if (OP1 == "%")
    {
        instr = new IRInstrMod((*bb), op1, op2, dest);
    }

    (*bb)->add_IRInstr(instr);

    return dest;
}

Expression *ExpressionOP1::getExpression()
{
    return nullptr;
}

ExpressionOP1::~ExpressionOP1()
{
    delete (expr1);
    delete (expr2);
}