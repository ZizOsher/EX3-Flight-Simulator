#include "Parser.h"
#include "Commands.h"
#include "CommandMap.h"
using namespace std;

void Parser::parse(vector<string> LexerResult) {
    itr index = LexerResult.begin();
    while (index != LexerResult.end()) {
        // itr is iterator for the string and *index is a string itself
        Command *command = CommandMap::getInstance().getCommand(*index);
        // if the command exists
        if (command != NULL) {
            index += command->execute(index);
        }
    }
}