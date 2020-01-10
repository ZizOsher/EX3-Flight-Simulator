#ifndef FLIGHT_SIMULATOR_LEXER_H
#define FLIGHT_SIMULATOR_LEXER_H
#include <string>
#include <vector>
#include <list>

using namespace std;
class Lexer {
    public:
        static vector<string> lexer(string filename);
        static list<string> split(string input, char delimiter, size_t splitLimit);
};

#endif //FLIGHT_SIMULATOR_LEXER_H