#include "ExpressionOPShift.h"

ExpressionOPShift::ExpressionOPShift(Expression *expr1, string OPShift, Expression *expr2)
{
    this->expr1 = expr1;
    this->OPShift = OPShift;
    this->expr2 = expr2;
}

string ExpressionOPShift::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionOPShift starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string op1 = expr1->getIR(bb);
    string op2 = expr2->getIR(bb);
    string dest = (*bb)->cfg->symbolTable->create_new_tempvar();
    
    IRInstr *instr; 
    if(OPShift == ">>")
    {
        instr = new IRInstrShift((*bb), op1, op2, dest, true);
    }
    else if (OPShift == "<<")
    {
        instr = new IRInstrShift((*bb), op1, op2, dest, false);
    }

    (*bb)->add_IRInstr(instr);

    return dest;
}

Expression *ExpressionOPShift::getExpression()
{
    return nullptr;
}

ExpressionOPShift::~ExpressionOPShift()
{
    delete (expr1);
    delete (expr2);
}