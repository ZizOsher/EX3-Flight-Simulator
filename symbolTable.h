//
// Created by hadar on 26/12/2019.
//

#ifndef UNTITLED1_SYMBOLTABLE_H
#define UNTITLED1_SYMBOLTABLE_H
#include <unordered_map>
#include <string>
#include "Commands.h"

using namespace std;

class symbolTable {

private:
    symbolTable();
    //using pointer to connect between stirng and command in hash function
    // because int as a pointer has a hash function
    unordered_map <string, Command*> commandMap;

public:

    symbolTable(symbolTable const&) = delete;
    // in = we create a new copy of the map;
    void operator= (symbolTable const&) = delete;

    static symbolTable& getInstance();
    Command* getCommand(string symbol);
    bool isInMap(string symbol);
    void addCommand(string symbol, Command* command);
};


#endif //UNTITLED1_SYMBOLTABLE_H
