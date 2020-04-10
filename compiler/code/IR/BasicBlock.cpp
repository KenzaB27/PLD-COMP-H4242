#include "BasicBlock.h"

BasicBlock::BasicBlock(CFG *cfg, string entry_label): cfg(cfg), label(entry_label) {
    this->conditionalExit = nullptr;    /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
    this->exit = nullptr;   /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
}

/*
    Generate asembly code
*/
void BasicBlock::gen_asm(ostream &o)
{
    if(printed == false) {
        printed = true;
    } else {
        return; 
    }


    if(label != MAIN) {//for main block 
        o << label << ":" <<endl;
    }

    if (this->label == ".return") { //we reach the last bb
        #ifdef DEBUG
            cout << "epilog generating" << endl ;
        #endif
        this->instrs[0]->gen_asm(o);
        this->cfg->gen_asm_epilogue(o); // generation of epilogue
        #ifdef DEBUG
            cout << "epilog generated" << endl ;
        #endif
        return;
    }

    for (auto instr : instrs) { //go over all instruction and generate their assembly code
        #ifdef DEBUG
        cout << "gen asm instr " << instr << endl ;
        #endif
        instr->gen_asm(o);
    }

    #ifdef DEBUG
        cout << "this->cfg->symbolTable : " << this->cfg->symbolTable << endl ;
        cout << "exit : " << exit << endl ;
        cout << "conditionalExit : " << conditionalExit << endl ;
    #endif
    
    if(conditionalExit != nullptr && condition.compare("")) { // two successors, if case
        string conditionAddr = this->cfg->symbolTable->IR_reg_to_asm(condition);
        o << "    cmpl    $0, " + conditionAddr << endl; //?????????? o << "cmpl "+test_var_name+"\r\n"; // assembly code comparing the value of test_var_name to true is generated
        o << "    je    " + exit->label << endl;  // else (condition false) -> conditional branch to the exit_false branch
        o << "    jmp    " + conditionalExit->label << endl;   // if condition true -> unconditional branch to the exit_true branch
    }
    else if (exit->getUnconditionalJump() != nullptr)
    {
        o << "    jmp    " + exit->label << endl; // an unconditional jmp to the exit_true branch is generated
    }
    #ifdef DEBUG
        cout << "almost" << endl ;
    #endif

    if (conditionalExit != nullptr){
        #ifdef DEBUG
            cout << "Entering conditionalExit Block" << endl ;
        #endif
        conditionalExit->gen_asm(o);
    }
    if(exit != nullptr){
        #ifdef DEBUG
            cout << "Entering next Block" << endl ;
        #endif
        exit->gen_asm(o);
    }

    #ifdef DEBUG
        cout << "ended" << endl ;
    #endif
}

void BasicBlock::setConditionalJump(BasicBlock *bb) {
    conditionalExit = bb;
}

void BasicBlock::setUnconditionalJump(BasicBlock *bb) {
    exit = bb;
}


BasicBlock *BasicBlock::getConditionalJump() {
    return conditionalExit;
}

BasicBlock *BasicBlock::getUnconditionalJump() {
    return exit;
}


void BasicBlock::setCondition(string v) {
    condition = v;
}

/*
    Add to the Basic Block's instructions to achieve the IRInstr passed in parameters (described by an operator, a type
    and list of parameters)
*/
void BasicBlock::add_IRInstr(IRInstr* instr) {
    instrs.push_back(instr);
}