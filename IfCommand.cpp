#include "Command.h"
#include "Interpreter.h"
#include <iostream>

int IfCommand::execute(itr itr1) {
    Interpreter &i = Interpreter::getInstance();
    int ret = 0;
    buildScope(itr1);
    for (Command *c : this->innerCommands) {
        ret += c->getSteps();
    }
    itr1++;
    string condition = *itr1;
    itr1 += 1;
    bool con = i.interpretCondition(condition);
    if (*itr1 == "{") {
        itr1++;
    }
    if (con) {
        int executed = 0;
        for (Command *c : this->innerCommands) {
            executed += c->execute(itr1 + executed);
        }
    }
    this->innerCommands.clear();
    return (this->getSteps() + ret + 1);
}

IfCommand::~IfCommand() {
    this->innerCommands.clear();
}
