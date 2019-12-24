/*
#ifndef UNTITLED1_COMMANDS_H
#define UNTITLED1_COMMANDS_H
#include "vector"
#include <unordered_map>
#include <string>
using namespace std;

class Command{

public:
    // abstract class
    virtual int exectue()=0;
};

class OpenServerCommand: public Command{
public:
    int exectue();
};

class ConccetCommand: public Command{
    int exectue();

};

class DefineVarCommanc: public Command{
    int exectue();
};

class Parser{
private:
    unordered_map <string, Command> myMap;
public:
    void parser(vector<string> myVector);
};

#endif //UNTITLED1_COMMANDS_H
*/