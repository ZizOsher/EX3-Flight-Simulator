
#ifndef UNTITLED1_COMMANDS_H
#define UNTITLED1_COMMANDS_H
#include <vector>
#include <unordered_map>
#include <string>
#include "Server.h"

using namespace std;

typedef vector<string>::iterator itr;
class Command{
    public:
        // abstract class
        virtual int execute(itr itr1) = 0;
};

class OpenServerCommand: public Command{
    public:
        int execute(itr itr1)override;
};

class ConnectCommand: public Command{
    int execute(itr itr1)override;

};

class DefineVarCommand: public Command{
    int execute(itr itr1)override;
};

#endif //UNTITLED1_COMMANDS_H
