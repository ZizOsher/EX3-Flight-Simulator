#ifndef UNTITLED1_SYMBOLTABLE_H
#define UNTITLED1_SYMBOLTABLE_H
#include <unordered_map>
#include <string>
#include "Command.h"
#include "Expressions.h"

using namespace std;

class SymbolTable {

private:
    SymbolTable();
    //using pointer to connect between the name of a variable and its object.
    // because int as a pointer has a hash function
    unordered_map <string, Variable*> symbolTable;

public:
    SymbolTable(SymbolTable const&) = delete;
    // in = we create a new copy of the map;
    void operator= (SymbolTable const&) = delete;

    static SymbolTable& getInstance();
    Variable* getVariable(string symbol);
    bool isInMap(string symbol);
    void addVariable(string symbol, Variable* var);
};

#endif //UNTITLED1_SYMBOLTABLE_H
