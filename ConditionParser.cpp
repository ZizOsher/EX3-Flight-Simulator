//
// Created by osher on 08/01/2020.
//
#include "Command.h"
#include "SymbolTable.h"
#include "CommandMap.h"
#include <iostream>
void ConditionParser::buildScope(itr itr1) {
    cout << "fishing for" << endl;
    SymbolTable& symTable = SymbolTable::getInstance();
    CommandMap& commie = CommandMap::getInstance();
    itr1 += 4;
    cout << *itr1 << endl;
    while (*itr1 != "}") {
        if (*itr1 != "\n") {
            Command* command;
            string commandName;
            cout << commandName << endl;
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
    cout << "fishies" << endl;
}
