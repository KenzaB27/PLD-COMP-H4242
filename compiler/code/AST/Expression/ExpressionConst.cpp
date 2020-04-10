#include "ExpressionConst.h"

ExpressionConst::ExpressionConst(string value)
{
    this->value = value;
}

ExpressionConst::ExpressionConst(string name, string op, string value)
{
    this->name = name; 
    this->op = op ; 
    this->value = value;
}

Expression *ExpressionConst::getExpression()
{
    return nullptr;
}

string ExpressionConst::getIR(BasicBlock **bb)
{

    #ifdef DEBUG
        cout << "getIR ExpressionConst starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif
    string dest =(*bb)->cfg->symbolTable->create_new_tempvar();
    #ifdef DEBUG
        cout << "DEBUG CONST VALUE " << value << endl; 
        cout << "DEBUG TEMP VARNAME" << dest << endl;   
    #endif
        IRInstr *instr;
        if (name == "")
        {
            instr = new IRInstrLdconst((*bb), value, dest);
        } 
        else {
            instr = new IRInstrConstVal((*bb), name, op, value, dest);
        }
        (*bb)->add_IRInstr(instr);
    #ifdef DEBUG
        cout << "getIR ExpressionConst ending" << dest << endl;
    #endif
    return dest;
}

string ExpressionConst::getValue()
{
    return value;
}

string ExpressionConst::getName()
{
    return name;
}

ExpressionConst::~ExpressionConst()
{

}