#include "Command.h"
#include "Interpreter.h"

int IfCommand::execute(itr itr1) {
    Interpreter &i = Interpreter::getInstance();
    int ret = 0;
    buildScope(itr1);
    for (Command *c : this->innerCommands) {
        ret += c->getSteps();
    }
    itr1++;
    string condition = *itr1;
    itr1 += 2;
    bool con = i.interpretCondition(condition);
    if (con) {
        //cout << "cond: " << condition << " val: " << i.interpretCondition(condition) << endl;
        int executed = 0;
        for (Command *c : this->innerCommands) {
            //cout << "*(itr1 + executed) = " << *(itr1 + executed) << endl;
            //cout << "*(itr1 + executed +2) = " << *(itr1 + executed +2) << endl;
            executed += c->execute(itr1 + executed);
        }
    }
    this->innerCommands.clear();
    return (this->getSteps() + ret + 1);
}