//
// Created by osher on 05/01/2020.
//
#include "Command.h"
#include "Expressions.h"
#include "SymbolTable.h"

using namespace std;

int DefineVarCommand::execute(itr itr1) {
    SymbolTable& symTable = SymbolTable::getInstance();
    Variable* res;
    string name = *itr1;
    itr1++;
    string bind = *itr1;
    if (bind == "<-" || bind == "->") {
        itr1++;
        string sim = *itr1;
        if (bind == "<-") {
            // TODO: Get from map created by server
        } else {
            res = new Variable(name, sim, true);
        }
    } else if (bind == "=") {
        itr1++;
        string nameOfOtherVar = *itr1;
        Variable* res = symTable.getVariable(nameOfOtherVar);
    }
    symTable.addVariable(name, res);
    return 4;
}