#pragma once

#include <vector>

#include "Structure.h"
#include "../../Expression/Expression.h"
#include "../../Block.h"
#include "../InstructionLine/InstructionLine.h"
#include "../CodeLine.h"
#include "../../../IR/BasicBlock.h"
#include "../../../IR/CFG.h"

class WhileCode : public Structure
{

public:
    WhileCode(Expression *expr, Block *b)
    {
        this->condition = expr;
        this->block = b;
    };

    /* WhileCode(Expression * expr, InstructionLine * i) { 
        vector<CodeLine*> instr;
        instr.push_back((CodeLine*) i);
        this->block = new Block(instr);
        this->condition = expr;
    }; */

    string getIR(BasicBlock **bb)
    {
#ifdef DEBUG
        cout << "getIR WhileCode starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
#endif
        string conditionRegisterBeforeWhile = this->condition->getIR(bb);                 // verification de la condition avant le while
        BasicBlock *bbWhile = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name());      // creation du BB qui contiendra les instructions du while
        BasicBlock *bbAfterWhile = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name()); // creation du BB qui contiendra les instructions d'après
        bbWhile->setUnconditionalJump(bbAfterWhile);

        (*bb)->cfg->add_bb(bbWhile);      // ajout du block while au CGF
        (*bb)->cfg->add_bb(bbAfterWhile); // ajout du block qui correspond à la sortie du while au CFG

        bbAfterWhile->setUnconditionalJump((*bb)->getUnconditionalJump()); // donner la sortie du bb courant au prochain bb après le While, pour qu'il ait toujours un bloc suivant
        
        (*bb)->setCondition(conditionRegisterBeforeWhile); // si cette condition est vérifiée
        (*bb)->setConditionalJump(bbWhile);                // alors on rentre dans la boucle while
        (*bb)->setUnconditionalJump(bbAfterWhile);

        *((*bb)->cfg->getBreakBlock()) = bbAfterWhile; //on set le breakBB du bb à bbOut

        BasicBlock **bbWhilePointer = new BasicBlock *;
        (*bbWhilePointer) = bbWhile;

        block->getIR(bbWhilePointer); // lecture des codelines du block while, qui sont mises dans le bbWhile

        string conditionRegisterDuringWhile = this->condition->getIR(bbWhilePointer); // verification de la condition du while, à la fin du block
        (*bbWhilePointer)->setCondition(conditionRegisterDuringWhile);
        (*bbWhilePointer)->setConditionalJump(bbWhile); // si la future condition est verifiée on recommence la boucle

        *bb = bbAfterWhile; // à la sortie du while le bloc courant est le bbAfterWhile, utilisé par la suite
        return "";
    }

    ~WhileCode()
    {
        delete condition;
        delete block;
    };

private:
    Expression *condition;
    Block *block;
};