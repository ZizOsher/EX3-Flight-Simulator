//
// Created by osher on 05/01/2020.
//

#ifndef UNTITLED1_SIMINCOMINGINFO_H
#define UNTITLED1_SIMINCOMINGINFO_H
#include <unordered_map>
#include <string>
#include "Command.h"
#include "Expressions.h"

using namespace std;

class SimIncomingInfo {

private:
    SimIncomingInfo();
    //using pointer to connect between the name of a variable and its object.
    // because int as a pointer has a hash function
    unordered_map <string, double> simIncomingInfo;

public:
    SimIncomingInfo(SimIncomingInfo const&) = delete;
    // in = we create a new copy of the map;
    void operator= (SimIncomingInfo const&) = delete;

    static SimIncomingInfo& getInstance();
    double getValue(const string& symbol);
    bool isInMap(const string& symbol);
    void addValue(const string& symbol, double d);
};

#endif //UNTITLED1_SIMINCOMINGINFO_H
