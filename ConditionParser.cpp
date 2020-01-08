//
// Created by osher on 08/01/2020.
//
#include "Command.h"
#include "SymbolTable.h"
#include "CommandMap.h"

void ConditionParser::buildScope(itr itr1) {
    SymbolTable& symTable = SymbolTable::getInstance();
    CommandMap& commie = CommandMap::getInstance();
    itr1 += 3;
    while (*itr1 != "}") {
        if (*itr1 != "\n") {
            Command* command;
            string commandName;
            if (symTable.getVariable(*itr1) != nullptr) {
                commandName = "variableAssignment";
            } else {
                commandName = *itr1;
            }
            command = commie.getCommand(commandName);
            innerCommands.push_back(command);
            itr1 += command->getSteps();
        } else {
            itr1++;
        }
    }
}
