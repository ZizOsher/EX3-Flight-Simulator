#ifndef UNTITLED1_PARSER_H
#define UNTITLED1_PARSER_H

#include "Command.h"
#include "vector"
#include "unordered_map"
#include <thread>

using namespace std;

class Parser {
public:
    static void parse(vector<string> LexerResult);
};


#endif //UNTITLED1_PARSER_H
