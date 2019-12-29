#include "Parser.h"
#include "Commands.h"
#include "CommandMap.h"
using namespace std;

void Parser:: parse(vector<string> myVector) {
    itr index = myVector.begin();
    while (index != myVector.end()) {
        // itr is itertor for the string and *index is a string itself
        Command *command = CommandMap::getInstance().getCommand(*index);
        // if the command is exsists
        if (command != NULL) {
            index += command->exectue(index);
        }
    }
}