
#include <iostream>
#include "Command.h"
#include "Interpreter.h"

using namespace std;

int PrintCommand::execute(itr itr1) {
    itr1++;
    string printable = *itr1;
    if (printable[0] == '"') {
        cout << printable << endl;
    } else {
        Interpreter& i = Interpreter::getInstance();
        double res = i.interpret(printable)->calculate();
        cout << res << endl;
    }
    return this->getSteps();
}

int PrintCommand::getSteps() {
    return this->steps;
}
