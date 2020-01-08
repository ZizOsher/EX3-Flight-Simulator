#include "Command.h"
#include "Interpreter.h"
#include "SymbolTable.h"
#include "CommandMap.h"

bool parseCondition() {
    return true;
}

int IfCommand::execute(itr itr1) {
    int ret = 0;
    itr1++;
    buildScope(itr1);
    for (Command* c : this->innerCommands) {
        ret += c->getSteps();
        ret++; // To account for \n
    }
    itr1++;
    if (parseCondition()) {
        int executed;
        for (Command* c : this->innerCommands) {
            executed += 1;
            executed += c->execute(itr1 + executed);
        }
    }
    return (this->getSteps() + 1 + ret);
}