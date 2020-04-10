#pragma once

#include "Structure.h"
#include "../../Expression/Expression.h"
#include "../../Block.h"
#include "../InstructionLine/InstructionLine.h"
#include "../CodeLine.h"

class IfCode {

public:

    IfCode(Expression * e, Block* b) { // unique if condition
        this->block = b;
        this->condition = e;
    };

    /* IfCode(Expression * e, InstructionLine * i) { // unique if condition
        vector<CodeLine*> instr;
        instr.push_back((CodeLine*) i);
        this->block = new Block(instr);
        this->condition = e;
    }; */

    ~IfCode() {
        delete condition;
        delete block;
    };

    Expression * getCondition() {
        return condition;
    };

    Block * getBlock() {
        return block;
    };
    
private:

    Expression * condition;
    Block * block;
};