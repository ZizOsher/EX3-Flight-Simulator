//
// Created by hadar on 26/12/2019.
//

#include "CommandMap.h"


CommandMap& CommandMap::getInstance() {
    static CommandMap oneInstance;
    return oneInstance;
}

Command *CommandMap::getCommand(string symbol) {
    return this->commandMap[symbol];
}

void CommandMap::addCommand(string symbol, Command* command) {
    this->commandMap[symbol]=command;
}

CommandMap::~CommandMap() {
    this->commandMap.clear();
}

