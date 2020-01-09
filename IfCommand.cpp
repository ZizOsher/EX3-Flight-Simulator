#include "Command.h"
#include "Interpreter.h"
#include "SymbolTable.h"
#include "CommandMap.h"

int IfCommand::execute(itr itr1) {
    int ret = 0;
    itr1++;
    buildScope(itr1);
    for (Command* c : this->innerCommands) {
        ret += c->getSteps();
    }
    itr1++;
    if (Interpreter::getInstance().interpretCondition(*itr1)) {
        int executed;
        for (Command* c : this->innerCommands) {
            executed += 1;
            executed += c->execute(itr1 + executed);
        }
    }
    return (this->getSteps() + 1 + ret);
}