
#include <iostream>
#include "Command.h"
#include "Interpreter.h"

using namespace std;

int PrintCommand::execute(itr itr1) {
    itr1++;
    string printable = *itr1;
    if (printable[0] == '"') {
        int len = printable.size() - 2;
        printable = printable.substr(1, len);
        cout << printable << endl;
    } else {
        Interpreter& i = Interpreter::getInstance();
        double res = i.interpret(printable)->calculate();
        cout << res << endl;
/*        if (res != 0) {
        }*/
    }
    return this->getSteps();
}

int PrintCommand::getSteps() {
    return this->steps;
}
