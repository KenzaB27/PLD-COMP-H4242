#pragma once

#include <vector>
#include "Structure.h"
#include "../InstructionLine/Instruction/Instruction.h"
#include "../../Expression/Expression.h"
#include "../InstructionLine/InstructionLine.h"

class ForCode : public Structure
{
private:
    /* data */
    InstructionLine *initialisation;
    Expression *condition;
    Instruction *iteration;
    Block *block;

public:
    ForCode(InstructionLine *initialisation, Expression *condition, Instruction *iteration, Block *block)
    {
        this->initialisation = initialisation;
        this->condition = condition;
        this->iteration = iteration;
        this->block = block;
    }

    string getIR(BasicBlock **bb)
    {
#ifdef DEBUG
        cout << "getIR ForCode starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
#endif
        //Init
        initialisation->getIR(bb);

        //Test conditionnel
        string conditionBefore = this->condition->getIR(bb);
        BasicBlock *bbIn = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name());
        BasicBlock *bbOut = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name());
        bbIn->setUnconditionalJump(bbOut);

        (*bb)->cfg->add_bb(bbIn);                                   // ajout du block for au CGF
        (*bb)->cfg->add_bb(bbOut);                                  // ajout du block qui correspond à la sortie du while au CFG

        bbOut->setUnconditionalJump((*bb)->getUnconditionalJump()); // donner la sortie du bb courant au prochain bb après le While, pour qu'il ait toujours un bloc suivant

        *((*bb)->cfg->getBreakBlock()) = bbOut; //on set le breakBB du bb à bbOut

        (*bb)->setCondition(conditionBefore);
        (*bb)->setConditionalJump(bbIn);
        (*bb)->setUnconditionalJump(bbOut);

        BasicBlock **bbInPointer = new BasicBlock *;
        (*bbInPointer) = bbIn;

        block->getIR(bbInPointer);     // lecture des codelines du block while, qui sont mises dans le bbWhile
        iteration->getIR(bbInPointer); // ajout de l'instruction itérative du for au bb
        string conditionAfter = this->condition->getIR(bbInPointer);
        (*bbInPointer)->setCondition(conditionAfter);
        (*bbInPointer)->setConditionalJump(bbIn);

        *(bb) = bbOut; // à la sortie du while le bloc courant est le bbAfterWhile, utilisé par la suite
        return "";
    }

    ~ForCode()
    {
        delete (initialisation);
        delete (condition);
        delete (iteration);
        delete (block);
    }
};
