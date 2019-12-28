#include "Parser.h"
using namespace std;

void Parser:: parser(vector<string> myVector) {
    itr index = myVector.begin();
    while (index != myVector.end()) {
        // itr is itertor for the string and *index is a string itself
        Command *command = symbolTable::getInstance().getCommand(*index);
        // if the command is exsists
        if (command != NULL) {
            index += command->exectue(index);
        }
    }
}