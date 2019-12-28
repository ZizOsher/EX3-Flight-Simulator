//
// Created by hadar on 26/12/2019.
//

#include "symbolTable.h"

symbolTable::symbolTable(){}

symbolTable& symbolTable::getInstance() {
    static symbolTable oneInstance;
    return oneInstance;
}

Command *symbolTable::getCommand(string symbol) {

    return this->commandMap[symbol];
}

bool symbolTable::isInMap(string symbol) {
    return this->commandMap.find(symbol)!= this->commandMap.end();
}

void symbolTable::addCommand(string symbol, Command* command) {
    this->commandMap[symbol]=command;
}
