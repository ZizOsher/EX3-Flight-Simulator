//
// Created by osher on 08/01/2020.
//
#include "Command.h"
#include "SymbolTable.h"
#include "CommandMap.h"
#include <iostream>
void ConditionParser::buildScope(itr itr1) {
    cout << "Building scope: " << endl;
    SymbolTable& symTable = SymbolTable::getInstance();
    CommandMap& commie = CommandMap::getInstance();
    itr1 += 3;
    cout << *itr1 << endl;
    while (*itr1 != "}") {
        if (*itr1 != "\n") {
            Command* command;
            string commandName;
            if (symTable.getVariable(*itr1) != nullptr) {
                commandName = "variableAssignment";
            } else {
                commandName = *itr1;
            }
            cout << "command name: " << commandName << endl;
            command = commie.getCommand(commandName);
            innerCommands.push_back(command);
            itr1 += command->getSteps();

        } else {
            itr1++;
        }
    }
    cout << "scope built" << endl;
}

int ConditionParser::getSteps() {
    return this->steps;
}
