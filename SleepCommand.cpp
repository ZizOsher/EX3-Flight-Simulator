
#include "SleepCommand.h"
void SleepCommand::sleepFor(int milisceondsSleep) {

    // Sleep this thread
    this_thread::sleep_for(std::chrono::milliseconds(milisceondsSleep));
}