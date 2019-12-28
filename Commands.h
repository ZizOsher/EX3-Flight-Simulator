
#ifndef UNTITLED1_COMMANDS_H
#define UNTITLED1_COMMANDS_H
#include <vector>
#include <unordered_map>
#include <string>
#include "symbolTable.h"
#include "Server.h"

using namespace std;

typedef vector<string>::iterator itr;
class Command{

public:
    // abstract class
    virtual int exectue(itr itr1)=0;
};

class OpenServerCommand: public Command{
public:
    int exectue(itr itr1)override ;
};

class ConccetCommand: public Command{
    int exectue(itr itr1)override ;

};

class DefineVarCommanc: public Command{
    int exectue(itr itr1)override ;
};

#endif //UNTITLED1_COMMANDS_H
