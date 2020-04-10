#pragma once

#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"
#include "../../../Expression/Expression.h"
#include <vector>
#include <string>

#include "Assignement.h"

class AssignAndDeclare : public Assignement
{
private:
    /* data */
    vector<string> identifiers;
    Expression* expr;

public:
    AssignAndDeclare(vector<string> identifiers, Expression *expr)
    {
        this->identifiers = identifiers;
        this->expr= expr;
    }

    string getIR(BasicBlock **bb){
        #ifdef DEBUG
        cout << "getIR AssignAndDeclare starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        string source = expr->getIR(bb);
        IRInstr *instr;
        if (identifiers.size() == 1)
        {
            
            (*bb)->cfg->symbolTable->add_to_symbol_table(identifiers[0]);
            instr = new IRInstrRMem(*bb, source, identifiers[0]);
        }
        else
        {
            for (auto identifier : identifiers)
            {
                (*bb)->cfg->symbolTable->declare_to_symbol_table(identifier);
            }
            (*bb)->cfg->symbolTable->assign_to_symbol_table(identifiers[identifiers.size() - 1]);
            instr = new IRInstrRMem(*bb, source, identifiers[identifiers.size()-1]);
        }
        (*bb)->add_IRInstr(instr);
        return "";
    }
    ~AssignAndDeclare()
    {
        delete(expr);
    }
};