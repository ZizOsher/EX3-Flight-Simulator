//
// Created by osher on 05/01/2020.
//

#include "Expressions.h"
#include "SymbolTable.h"


SymbolTable::SymbolTable(){}

SymbolTable& SymbolTable::getInstance() {
    static SymbolTable oneInstance;
    return oneInstance;
}

Variable* SymbolTable::getVariable(const string symbol) {
    return this->symbolTable[symbol];
}

bool SymbolTable::isInMap(const string symbol) {
    return this->symbolTable.find(symbol) != this->symbolTable.end();
}

void SymbolTable::addVariable(const string symbol, Variable* variable) {
    this->symbolTable[symbol] = variable;
}
