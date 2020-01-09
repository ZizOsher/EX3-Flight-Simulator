#include "Command.h"
#include "Interpreter.h"
#include "math.h"

void SleepCommand::sleepFor(int milisceondsSleep) {
    // Sleep this thread
    this_thread::sleep_for(std::chrono::milliseconds(milisceondsSleep));
}

int SleepCommand::execute(itr itr1) {
    itr1++;
    Interpreter& i = Interpreter::getInstance();
    int sleepingTime = round(i.interpret(*itr1)->calculate());
    this->sleepFor(sleepingTime);
    return this->getSteps();
}

int SleepCommand::getSteps() {
    return this->steps;
}
