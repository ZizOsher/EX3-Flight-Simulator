//
// Created by osher on 05/01/2020.
//
#include "Command.h"
#include "Expressions.h"
#include "SymbolTable.h"
#include "SimIncomingInfo.h"
#include <iostream>

using namespace std;

int DefineVarCommand::execute(itr itr1) {
    SymbolTable& symTable = SymbolTable::getInstance();
    Variable *res = nullptr;
    itr1++;
    //cout << *itr1 << ",";
    const string name = *itr1;
    itr1++;
    //cout << *itr1 << ",";

    string bind = *itr1;
    if (bind == "<-" || bind == "->") {
        itr1 += 2;
        //cout << *itr1 << ",";

        string sim = *itr1;
        size_t pos = sim.size() - 1;
        if (sim[0] == '"' && sim[pos] == '"') {
            sim = sim.substr(1, pos - 1);
        }
        if (bind == "<-") {
            double value = SimIncomingInfo::getInstance().getValue(name);
            res = new Variable(name, value, sim, false);
        } else {
            res = new Variable(name, sim, true);
        }
        //symTable.addVariable(name, res);
    } else if (bind == "=") {
        itr1++;
        string nameOfOtherVar = *itr1;
        Variable* res = symTable.getVariable(nameOfOtherVar);
    }
    symTable.addVariable(name, res);
    if (symTable.getVariable(name) != nullptr) {
        //cout << symTable.getVariable(name);
    }
    //cout << endl;
    return 5;
}