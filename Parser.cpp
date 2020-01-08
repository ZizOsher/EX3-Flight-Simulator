#include "Parser.h"
#include "Command.h"
#include "CommandMap.h"
#include "SymbolTable.h"
#include <iostream>
using namespace std;

// TODO: MAKE THAT MOTHERFUCKER FUCKING FLYYYYYYYYYYY

void Parser::parse(vector<string> LexerResult) {
    itr index = LexerResult.begin();
    while (index != LexerResult.end()) {
        if (*index != "\n") {
            string symbol;
            if (SymbolTable::getInstance().getVariable(*index) != nullptr) {
                symbol = "variableAssignment";
            } else {
                symbol = *index;
            }
            //cout << *index << endl;
            // itr is iterator for the string and *index is a string itself
            Command *command = CommandMap::getInstance().getCommand(symbol);
            // if the command exists
            if (command != nullptr) {
                index += command->execute(index);
            }
        } else {
            index++;
        }
    }
}