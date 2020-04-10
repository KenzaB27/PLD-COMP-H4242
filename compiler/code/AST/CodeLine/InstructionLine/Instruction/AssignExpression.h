#pragma once

#include "Instruction.h"
#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"
#include "../../../Expression/Expression.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrAdd.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrDiv.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrMul.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrSub.h"
#include "../../../../colors.h"


class AssignExpression : public Instruction
{
private:
    /* data */
    Expression *expression;
    string affect;
    string identifier;

public:
    AssignExpression(string identifier, string affect, Expression *expression)
    {
        this->expression = expression;
        this->identifier = identifier;
        this->affect = affect;
    }

    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR AssignExpression starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        
        string addr = expression->getIR(bb);
        if (!(*bb)->cfg->symbolTable->exist_in_table(identifier))
        {
            //error :  id doesn't exist in the symbol table
            std::cerr <<BOLD(FRED("ERROR :" )) << "'"+identifier + "' does not exist in symbols table." << endl;
            exit(0);
        }
        (*bb)->cfg->symbolTable->assign_to_symbol_table(identifier);
        IRInstr *instr;
        if (affect == "=")
        {
            instr = new IRInstrRMem((*bb), addr, identifier);
        }
        else if (affect == "+=")
        {
            instr = new IRInstrAdd((*bb), addr, identifier, identifier);
        }
        else if (affect == "-=")
        {
            instr = new IRInstrSub((*bb), identifier, addr, identifier);
        }
        else if (affect == "*=")
        {
            instr = new IRInstrMul((*bb), addr, identifier, identifier);
        }
        else if (affect == "/=")
        {
            instr = new IRInstrDiv((*bb), identifier, addr, identifier);
        }
        (*bb)->add_IRInstr(instr);
        return "";
    }
    ~AssignExpression()
    {
        delete (expression);
    }
};
