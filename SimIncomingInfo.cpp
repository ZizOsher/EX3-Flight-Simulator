#include "SimIncomingInfo.h"

//TODO: Create interface for database style classes: SimIncomingInfo, SymbolTable, CommandMap.

SimIncomingInfo::SimIncomingInfo(){}

SimIncomingInfo& SimIncomingInfo::getInstance() {
    static SimIncomingInfo oneInstance;
    return oneInstance;
}

double SimIncomingInfo::getValue(const string& symbol) {
    return this->simIncomingInfo[symbol];
}

bool SimIncomingInfo::isInMap(const string& symbol) {
    return this->simIncomingInfo.find(symbol)!= this->simIncomingInfo.end();
}

void SimIncomingInfo::addValue(const string& symbol, double d) {
    this->simIncomingInfo[symbol] = d;
}
