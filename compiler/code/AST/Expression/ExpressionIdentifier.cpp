#include "ExpressionIdentifier.h"


ExpressionIdentifier::ExpressionIdentifier(string name)
{
    this->name = name;
}

string ExpressionIdentifier::getIR(BasicBlock **bb)
{
    #ifdef DEBUG
        cout << "getIR EpxressionIdentifier starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif
    return name;
}

Expression *ExpressionIdentifier::getExpression()
{
    return this;
} 
string ExpressionIdentifier::getName()
{
    return name; 
}
ExpressionIdentifier::~ExpressionIdentifier()
{

}