#pragma once 

#include <vector>
#include <map>

#include "./CodeLine/CodeLine.h"
#include "../IR/BasicBlock.h"
#include "CodeLine/Structure/Structure.h"

class Block : public Structure
{
private:
    /* data */
    vector <CodeLine *> codeLines; 
public:
    Block(vector<CodeLine *> codeLines)
    {
        this->codeLines = codeLines;
    }
    string getIR(BasicBlock **bb)
    {
        #ifdef DEBUG
        cout << "getIR Block starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif
        for (auto codeLine : codeLines)
        {
            codeLine->getIR(bb);
        }
        return "";
    }
    ~Block() {
        for (auto codeLine : codeLines)
        {
            delete(codeLine);
        }
    };
    void addCodeLine(CodeLine *codeline) {
        codeLines.push_back(codeline);
    };
    vector <CodeLine *> getCodelines() {
        return codeLines;
    };
    // void toString() {
    //     cout <<"[B] ### Début du bloc\r\n";
    //     int i = 0;
    //     while (i < codeLines.end() ) {
    //         codeLines[i]->toString();
    //         i++;
    //     }
    //     cout << "[B] ### Fin du bloc\r\n";
    // };
    //void resoudrePortees(int *globalContext, list<string> *varStack, std::map<std::string,Declaration *> *varMap, std::list<std::string> *fctStack);

};
