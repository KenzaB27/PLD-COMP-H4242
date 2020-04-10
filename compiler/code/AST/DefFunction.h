#pragma once 

#include "Block.h"
class DefFunction
{
private:
    /* data */
    Block *block;
    string name;  
public:
    DefFunction(Block *block, string name)
    {
        this->block = block;
        this->name = name;
    }
    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR DefFunction starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        block->getIR(bb);
        #ifdef DEBUG
        cout << "getIR DefFunction ending" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        return "";
    }
    string getName()
    {
        return name;
    }
    ~DefFunction()
    {
        delete (block);
    }
};

