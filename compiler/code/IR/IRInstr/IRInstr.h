#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

using namespace std;

// Declarations from the parser -- replace with your own
// #include "type.h"
#include "../BasicBlock.h"

class BasicBlock;

//! The class for one 3-address instruction
class IRInstr
{

public:
    /**  constructor */
    IRInstr(BasicBlock *bb_);
    IRInstr();
    /** Actual code generation */
    virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
    string transParam(string par);
    ~IRInstr();

protected:
    BasicBlock *bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    // Type t;
    //vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
                           // if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.
};
