//
// Created by osher on 23/12/2019.
//

#ifndef FLIGHT_SIMULATOR_LEXER_H
#define FLIGHT_SIMULATOR_LEXER_H
#include <map>
#include <string>
#include "Expression.h"
#include <vector>
#include <stack>

using namespace std;
class Lexer {
    public:
        list<string> lexer(string filename);
}


#endif //FLIGHT_SIMULATOR_LEXER_H
