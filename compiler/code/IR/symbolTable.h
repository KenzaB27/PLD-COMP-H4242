#pragma once


#include <map>
#include <vector>
#include <string>
#include <iostream>

#define INT_SIZE 4

using namespace std;

class SymbolTable {

    struct Variable {
        bool declared;
        bool defined;
        int level;
        int adress;
    };

    typedef map<string, Variable> SymbolIndexMap;

    public :
    SymbolTable();

    // symbol table methods
    void add_to_symbol_table(string name);
    void declare_to_symbol_table(string name);
    void assign_to_symbol_table(string name);

    bool exist_in_table(string name);
    string create_new_tempvar();
    string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    int get_var_index(string name);

    void enterContext();
    void exitContext();

    void check_var_usage();

    ~SymbolTable();

    //public var
    int nextFreeSymbolOffset = -INT_SIZE;
    int nextTempNumber = 0;

    protected :
    int context = 0;
    SymbolIndexMap symbolIndex;
};