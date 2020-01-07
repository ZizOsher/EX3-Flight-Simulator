#ifndef UNTITLED1_COMMANDMAP_H
#define UNTITLED1_COMMANDMAP_H

#include <unordered_map>
#include <string>
#include "Command.h"

using namespace std;

class CommandMap {

    private:
        CommandMap() {
            addCommand("openDataServer", new OpenServerCommand());
            addCommand("connectControlClient", new ConnectCommand());
            addCommand("var", new DefineVarCommand());
            addCommand("Print", new PrintCommand());
            addCommand("Sleep", new SleepCommand());
            addCommand("variableAssignment", new VarAssignCommand());
        }
        //using pointer to connect between string and command in hash function
        // because int as a pointer has a hash function
        unordered_map <string, Command*> commandMap;

    public:
        CommandMap(CommandMap const&) = delete;
        // in = we create a new copy of the map;
        void operator= (CommandMap const&) = delete;

        static CommandMap& getInstance();
        Command* getCommand(string symbol);
        bool isInMap(string symbol);
        void addCommand(string symbol, Command* command);
        //void buildCommandMap();
};


#endif //UNTITLED1_COMMANDMAP_H
