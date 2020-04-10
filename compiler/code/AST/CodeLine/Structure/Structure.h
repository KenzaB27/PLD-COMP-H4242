
#pragma once 

#include <list>

#include "../CodeLine.h"

class Structure : public CodeLine {

public:
    Structure() {};
    ~Structure() {};
    virtual string getIR(BasicBlock **bb)
    {
        return "";
    }
};
