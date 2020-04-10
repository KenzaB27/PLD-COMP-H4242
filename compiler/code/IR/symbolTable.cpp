#include "symbolTable.h"
#include "../colors.h"

SymbolTable::SymbolTable()
{
    add_to_symbol_table("_retvalue");
}

string SymbolTable::create_new_tempvar()
{
    string name = "@tmp" + to_string(nextTempNumber++);
    add_to_symbol_table(name);
    return name;
}

void SymbolTable::add_to_symbol_table(string name)
{
    auto it = symbolIndex.find(name);
    if (it != symbolIndex.end())
    {
        if (it->second.declared)
        {
            //error : variable  already exists in symbols table
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name << "' already exists in symbols table." << endl;
            exit(0);
        }
        else
        {
            it->second.level = context;
            it->second.declared = true;
            it->second.defined = true;
        }
    }
    else
    {
        Variable var;
        var.adress = nextFreeSymbolOffset;
        var.declared = true;
        var.defined = true;
        var.level = context;
        pair<SymbolIndexMap::iterator, bool> result = symbolIndex.insert({name, var});
        if (!result.second) //can't happen because checked before
        {
            //error : variable  already exists in symbols table
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name + "' already exists in symbols table." << endl;
            exit(0);
        }
        nextFreeSymbolOffset -= INT_SIZE;
    }
}

void SymbolTable::declare_to_symbol_table(string name)
{
    auto it = symbolIndex.find(name);
    if (it != symbolIndex.end())
    {
        if (it->second.declared)
        {
            //error : variable  already exists in symbols table
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name + "' already exists in symbols table." << endl;
            exit(0);
        }
        else
        {
            it->second.level = context;
            it->second.declared = true;
        }
    }
    else
    {
        Variable var;
        var.adress = 1;
        var.declared = true;
        var.defined = false;
        var.level = context;
        pair<SymbolIndexMap::iterator, bool> result = symbolIndex.insert({name, var});
        if (!result.second) //can't happen because checked before
        {
            //error : variable  already exists in symbols table
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name + "' already exists in symbols table." << endl;
            exit(0);
        }
    }
}

void SymbolTable::assign_to_symbol_table(string name)
{
    auto it = symbolIndex.find(name);
    if (it != symbolIndex.end())
    {
        if (it->second.declared)
        {
            if (!it->second.defined)
            {
                it->second.adress = nextFreeSymbolOffset;
                it->second.defined = true;
                nextFreeSymbolOffset -= INT_SIZE;
            }
        }
        else
        {
            //error : variable not declared
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name + "' not declared." << endl;
            exit(0);
        }
    }
    else
    {
        //error : variable not declared
        std::cerr << BOLD(FRED("ERROR :" ))<<"'"+name + "' not declared." << endl;
        exit(0);
    }
}

bool SymbolTable::exist_in_table(string name)
{
    auto it = symbolIndex.find(name);
    if (it != symbolIndex.end() && it->second.level >= context)
    {
        return true;
    }
    return false;
}

string SymbolTable::IR_reg_to_asm(string name)
{
    // cout << "DEBUG IR_reg_to_asm " << name << endl;*
    auto it = symbolIndex.find(name);
    if (it != symbolIndex.end())
    {
        if (it->second.defined && it->second.level >= context)
        {
            return to_string(it->second.adress) + "(%rbp)";
        }
        else
        {
            //error :  variable not assigned
            std::cerr << BOLD(FRED("ERROR :" ))<<"'"+name + "' not assigned." << endl;
            exit(0);
        }
    }
    else
    {
        //error : variable not defined
        std::cerr << BOLD(FRED("ERROR :" ))<<"'"+ name + "' not defined." << endl;
        exit(0);
    }
    return "";
}

void SymbolTable::enterContext()
{
    context++;
}

void SymbolTable::exitContext()
{
    for (auto it : symbolIndex)
    {
        if (it.second.level <= context)
        {
            it.second.declared = false;
            it.second.defined = false;
        }
    }
    context--;
}

void SymbolTable::check_var_usage()
{
    for (auto it : symbolIndex)
    {
        if (it.second.adress >= 0)
        {
            //warning : variable not used
            std::cerr << BOLD(FYEL("WARNING : " ))<<" variable '"+ it.first + "' not used." << endl;
        }
    }
}

SymbolTable::~SymbolTable()
{
}