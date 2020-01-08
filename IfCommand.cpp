#include "Command.h"
#include "Interpreter.h"

int IfCommand::execute(itr itr1) {
    itr1++;
    Interpreter& i = Interpreter::getInstance();
    if (false) {
        return 1;
    } else {
        return 0;
    }
}