
#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H
#include <vector>
#include <unordered_map>
#include <string>
#include <thread>
#include "Server.h"

using namespace std;

typedef vector<string>::iterator itr;
class Command {
    public:
        // abstract class
        virtual int execute(itr itr1) = 0;
};

class OpenServerCommand: public Command {
    private:
        // create thread only when it's needed
        thread* MyThread;
    public:
        int execute(itr itr1) override;
        void joinThread();
};

class ConnectCommand: public Command {
private:
    // create thread only when it's needed
    thread* clientThread;
public:
    int execute(itr itr1) override;
};

class DefineVarCommand: public Command {
    int execute(itr itr1) override;
};

class VarAssignCommand: public Command {
    int execute(itr itr1) override;
};

class PrintCommand: public Command {
    int execute(itr itr1) override;
    static void printText(string str);
};

class SleepCommand: public Command {
public:
    int execute(itr itr1) override;
    void sleepFor(int milisceondsSleep);
};

#endif //UNTITLED1_COMMAND_H
