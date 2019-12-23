#include <map>
#include <string>
#include <vector>
#include <stack>
#include "Lexer.h"

using namespace std;


vector<string> Lexer::lexer(string filename) {
    ifstream lexerInput(filename);
    string line;
    vector<string> commands;
    string seperators = '" ()';
    string defSepIn = "<-";
    string defSepOut = "->";


    unsigned int n;
    n = 0;
    while (getline(lexerInput, line)) {
        // check if we've reached a seperator
        if () {
            
        }
        n++;
    }
    lexerInput.close();
}