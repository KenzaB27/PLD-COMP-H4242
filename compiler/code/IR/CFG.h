#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

// Declarations from the parser -- replace with your own
#include "BasicBlock.h"
#include "symbolTable.h"
#include "../AST/DefFunction.h"

/* AST avec Programme, instructions etc. */

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	The entry block is the one with the same label as the AST function name.
	(it could be the first of bbs, or it could be defined by an attribute value)
	The exit block is the one with both exit pointers equal to nullptr.
    (again it could be identified in a more explicit way)
 */

#ifdef MACOS
#define MAIN "_main"
#else
#define MAIN "main"
#endif

class BasicBlock;
class Expression; 

class CFG
{
public:

    CFG(DefFunction *ast, SymbolTable *symbTab);

    void add_bb(BasicBlock *bb);

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(ostream &o);
    void gen_asm_prologue(ostream &o);
    void gen_asm_epilogue(ostream &o);

    BasicBlock **getCurrentBlock();
    BasicBlock *getReturnBlock();
    BasicBlock **getBreakBlock();

    // basic block management
    string new_BB_name();
    string new_RET_name();
    bool findBB(string label);

    SymbolTable* symbolTable;
    DefFunction* ast; /**< The AST this CFG comes from */
protected:
    // basic block management
    BasicBlock **current_bb;
    BasicBlock **break_bb;
    int nextBBnumber=0;        /**< just for naming */
    int nextRetNumber=0;
    vector <BasicBlock *> bbs; /**< all the basic blocks of this CFG*/
};