#include "ExpressionOPBool.h"

ExpressionOPBool::ExpressionOPBool(Expression *expr1, string OPBool, Expression *expr2)
{
    this->expr1 = expr1;
    this->OPBool = OPBool;
    this->expr2 = expr2;
}

string ExpressionOPBool::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR ExpressionOPBOOL starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif

    string op1 = expr1->getIR(bb);
    string op2 = expr2->getIR(bb);
    string dest = (*bb)->cfg->symbolTable->create_new_tempvar();

    IRInstr *instr; 
    if(OPBool == "==")
    {
        instr = new IRInstrCmp_eq((*bb), op1, op2, dest);
    }
    else if (OPBool == "!=")
    {
        instr = new IRInstrCmp_neq((*bb), op1, op2, dest);
    }
    else if (OPBool == ">")
    {
        instr = new IRInstrCmp_gt((*bb), op1, op2, dest);
    }
    else if (OPBool == ">=")
    {
        instr = new IRInstrCmp_ge((*bb), op1, op2, dest);
    }
    else if (OPBool == "<")
    {
        instr = new IRInstrCmp_lt((*bb), op1, op2, dest);
    }
    else if (OPBool == "<=")
    {
        instr = new IRInstrCmp_le((*bb), op1, op2, dest);
    }
    else if (OPBool == "^")
    {
        instr = new IRInstrXor((*bb), op1, op2, dest);
    }
    else if (OPBool == "&")
    {
        instr = new IRInstrAnd((*bb), op1, op2, dest);
    }
    else if (OPBool == "&&")
    {
        instr = new IRInstrDAnd((*bb), op1, op2, dest);
    }
    else if (OPBool == "|")
    {
        instr = new IRInstrOr((*bb), op1, op2, dest);
    }
    else if (OPBool == "||")
    {
        instr = new IRInstrDOr((*bb), op1, op2, dest);
    }

    (*bb)->add_IRInstr(instr);

    return dest;
}

Expression *ExpressionOPBool::getExpression()
{
    return nullptr;
}

ExpressionOPBool::~ExpressionOPBool()
{
    delete (expr1);
    delete (expr2);
}