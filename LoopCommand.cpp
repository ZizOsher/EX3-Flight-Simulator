#include "Command.h"
#include "Interpreter.h"
#include "SymbolTable.h"
#include "CommandMap.h"
#include <iostream>

int LoopCommand::execute(itr itr1) {
    Interpreter& i = Interpreter::getInstance();
    int ret = 0;
    //itr1++;
    buildScope(itr1);
    for (Command* c : this->innerCommands) {
        ret += c->getSteps();
    }
    itr1++;
    string condition = *itr1;
    cout << "cond: " << condition << " val: " << i.interpretCondition(condition) << endl;
    while (i.interpretCondition(condition)) { // Here be the skrewy part
        int executed = 0;
        for (Command* c : this->innerCommands) {
            //executed += 1;
            cout << *(itr1 + executed) << endl;
            executed += c->execute(itr1 + executed);
        }

    }
    return (this->getSteps() + ret);
}