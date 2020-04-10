#pragma once

#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"
#include "../../../Expression/Expression.h"
#include <vector>
#include <string>

#include "Assignement.h"

class Declare : public Assignement
{
private:
    /* data */
    vector<string> identifiers;

public:
    Declare(vector<string> identifiers)
    {
        this->identifiers = identifiers;
    }

    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR Declare starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        if (identifiers.size() == 1)
        {
            (*bb)->cfg->symbolTable->declare_to_symbol_table(identifiers[0]);
        }
        else
        {
            for (auto identifier : identifiers)
            {
                (*bb)->cfg->symbolTable->declare_to_symbol_table(identifier);
            }
        }
        return "";
    }
    ~Declare()
    {
    }
};