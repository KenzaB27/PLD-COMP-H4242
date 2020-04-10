#pragma once

#include "Instruction.h"
#include "../../../../IR/IRInstr/RWMnemonics/IRInstrRMem.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrAdd.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrDiv.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrMul.h"
#include "../../../../IR/IRInstr/ArithmeticMnemonics/IRInstrSub.h"
#include "../../../../colors.h"


class AssignInstruction : public Instruction
{
private:
    /* data */
    Instruction *instruction;
    string identifier;
    string affect;

public:
    AssignInstruction(string identifier, string affect, Instruction *instruction)
    {
        this->instruction = instruction;
        this->affect = affect;
        this->identifier = identifier;
    }
    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR AssignInstruction starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        string addr = instruction->getIR(bb);
        if (!(*bb)->cfg->symbolTable->exist_in_table(identifier))
        {
            // error : id doesn't exist in the symbol table
            std::cerr <<BOLD(FRED("ERROR :" ))<<"'"+ identifier + "' does not exist in the symbols table." << endl;
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
            instr = new IRInstrSub((*bb), addr, identifier, identifier);
        }
        else if (affect == "*=")
        {
            instr = new IRInstrMul((*bb), addr, identifier, identifier);
        }
        else if (affect == "/=")
        {
            instr = new IRInstrDiv((*bb), addr, identifier, identifier);
        }
        (*bb)->add_IRInstr(instr);
        return "";
    }
    ~AssignInstruction()
    {
        delete (instruction);
    }
};
