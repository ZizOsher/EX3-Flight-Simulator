#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H
#include <vector>
#include <unordered_map>
#include <string>
#include <thread>
#include "Server.h"
#include <list>

using namespace std;

extern int client_socket;
extern mutex mutex1;

typedef vector<string>::iterator itr;

class Command {
private:
    int steps;
public:
    // abstract class
    virtual int execute(itr itr1) = 0;
    virtual int getSteps() = 0;
    virtual ~Command() {};
};

class OpenServerCommand: public Command {
private:
    itr index;
    // create thread only when it's needed
    thread* MyThread;
    int steps = 2;
public:
    int execute(itr itr1) override;
    void joinThread();
    static void openServerToThread(itr itr1);
    int getSteps() override;
    ~OpenServerCommand();
};

class ConnectCommand: public Command {
private:
    // create thread only when it's needed
    thread* clientThread;
    int steps = 3;
public:
    int execute(itr itr1) override;
    static void openClientThread(itr itr1);
    int getSteps() override;
    ~ConnectCommand();
};

class DefineVarCommand: public Command {
private:
    int steps = 5;
public:
    int execute(itr itr1) override;
    int getSteps() override;
    virtual ~DefineVarCommand() {};
};

class VarAssignCommand: public Command {
private:
    int steps = 3;
public:
    int execute(itr itr1) override;
    int getSteps() override;
    virtual ~VarAssignCommand() {};

};

class PrintCommand: public Command {
private:
    int steps = 2;
public:
    int execute(itr itr1) override;
    int getSteps() override;
    virtual ~PrintCommand() {};
};

class SleepCommand: public Command {
private:
    int steps = 2;
public:
    int execute(itr itr1) override;
    void sleepFor(int milisceondsSleep);
    int getSteps() override;
    virtual ~SleepCommand() {};
};

class ConditionParser: public Command {
private:
    int steps = 3;
protected:
    list<Command*> innerCommands;
    int stepsInScope;
public:
    void buildScope(itr itr1);
    virtual int execute(itr itr1) = 0;
    int getSteps();
    virtual ~ConditionParser() {};
};

class IfCommand: public ConditionParser {
public:
    int execute(itr itr1) override;
    ~IfCommand();
};

class LoopCommand: public ConditionParser {
public:
    int execute(itr itr1) override;
    ~LoopCommand();

};

#endif //UNTITLED1_COMMAND_H