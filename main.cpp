#include <unistd.h>
#include <string>
#include <vector>
#include "Server.h"
#include "Command.h"
#include "Lexer.h"
#include "Parser.h"
#include <iostream>

using namespace std;
bool done;

int main(int argc, char const *argv[]) {
    /*if (argc == 1) {
        cout << "Cannot run without input file. Please try again." << endl;
        return 0;
    }*/
    done = false;
    vector<string> vectorofStrings;
    vectorofStrings = Lexer::lexer(argv[1]);
//    vectorofStrings = Lexer::lexer("fly.txt");
    Parser::parse(vectorofStrings);
    done = true;
    close(client_socket);
    return 0;
}