#include "CFG.h"
// antlr::parserRuleContext

CFG::CFG(DefFunction *ast, SymbolTable *symbTab) : nextBBnumber(0), ast(ast), symbolTable(symbTab), current_bb(new BasicBlock*)
{

    BasicBlock *firstBB = new BasicBlock(this,MAIN);
    *(this->current_bb) = firstBB;
    add_bb(firstBB);

    BasicBlock *return_bb = new BasicBlock(this, ".return");
    add_bb(return_bb);

    this->break_bb = new BasicBlock*(); 

    BasicBlock *lastBB = new BasicBlock(this, new_BB_name());
    add_bb(lastBB);

    firstBB->setUnconditionalJump(lastBB);


    #ifdef DEBUG
        cout << "CurrentBB Set !" << endl;
        cout << "Current BasicBlock is : " << *current_bb << " | addressed at: " << current_bb << endl;
        cout << "––––––––––––––––––––––––––––––" << endl;
    #endif
}

BasicBlock *CFG::getReturnBlock()
{
    return bbs[1];
}

BasicBlock **CFG::getBreakBlock()
{
    return this->break_bb;
}

BasicBlock **CFG::getCurrentBlock()
{
    return this->current_bb;
}

/* Warnings you have to maange the link between the basic blocks*/
void CFG::add_bb(BasicBlock *bb) 
{
    bbs.push_back(bb);
}

void CFG::gen_asm(ostream &o)
{
    gen_asm_prologue(o);
    //cout << "GEN_ASM " << bbs.size() << endl;
    bbs[0]->gen_asm(o);
}

void CFG::gen_asm_prologue(ostream &o)
{
    o << ".globl    " << MAIN << endl;
    o << MAIN << ": " << endl;
    o << "    pushq   %rbp" << endl;
    o << "    movq    %rsp, %rbp" << endl;
}

void CFG::gen_asm_epilogue(ostream &o)
{
    o << "    popq   %rbp" << endl;
    o << "    ret " << endl;
}

string CFG::new_BB_name()
{
    return "." + ast->getName() + "_bb_" + to_string(nextBBnumber++);
}

string CFG::new_RET_name()
{
    return ".ret_" + to_string(nextRetNumber++);
}

bool CFG::findBB(string label)
{
    for (auto bb : bbs)
    {
        if (bb->label == label)
        {
            return true; 
        }
    }
    return false;
}