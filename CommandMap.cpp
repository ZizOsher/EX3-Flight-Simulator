//
// Created by hadar on 26/12/2019.
//

#include "CommandMap.h"

CommandMap::CommandMap(){}

CommandMap& CommandMap::getInstance() {
    static CommandMap oneInstance;
    return oneInstance;
}

Command *CommandMap::getCommand(string symbol) {
    return this->commandMap[symbol];
}

bool CommandMap::isInMap(string symbol) {
    return this->commandMap.find(symbol)!= this->commandMap.end();
}

void CommandMap::addCommand(string symbol, Command* command) {
    this->commandMap[symbol]=command;
}

void CommandMap::buildCommandMap() {
    addCommand("OpenServerCommand", new OpenServerCommand());
    addCommand("connectControlClient", new ConnectCommand());
    addCommand("var", new DefineVarCommand());
    //addCommand("Print", new PrintCommand());
}