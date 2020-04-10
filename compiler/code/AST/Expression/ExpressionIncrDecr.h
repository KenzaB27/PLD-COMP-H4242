#pragma once

#include "Expression.h"
#include "../CodeLine/InstructionLine/Instruction/PostDecrement.h"
#include "../CodeLine/InstructionLine/Instruction/PreDecrement.h"
#include "../CodeLine/InstructionLine/Instruction/PostIncrement.h"
#include "../CodeLine/InstructionLine/Instruction/PreIncrement.h"

class ExpressionIncrDecr : public Expression
{
private:
    /* data */
    string identifier;
    int cas;
public:
    enum cases
    {
        PREINCREMENT,
        POSTINCREMENT,
        PREDECREMENT,
        POSTDECREMENT
    };
    Expression *getExpression()
    {
        return nullptr;
    }
    ExpressionIncrDecr(string identifier , int cas)
    {
        this->identifier = identifier;
        this->cas = cas;
    }
    string getIR(BasicBlock **bb)
    {
    #ifdef DEBUG
        cout << "getIR ExpressionIncrDecr starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
    #endif
        string dest = "";
        Instruction * instr = nullptr; 
        switch (cas)
        {
        case PREINCREMENT:
            instr = new PreIncrement (identifier);
            break;
        case POSTINCREMENT:
            instr = new PostIncrement(identifier);
            break;
        case PREDECREMENT:
            instr = new PreDecrement(identifier);
            break;
        case POSTDECREMENT:
            instr = new PostDecrement(identifier);
            break;
        default:
            break;
        }
        if (instr != nullptr)
        {
            dest = instr->getIR(bb);
        }
        return dest;
    }
    ~ExpressionIncrDecr()
    {
    }
};