#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "Server.h"
#include "Client.h"
#include "Command.h"
#include "Lexer.h"
#include "Parser.h"
#include <vector>
#include "Interpreter.h"
#include "Expressions.h"

using namespace std;
bool done;

int main(int argc, char const *argv[]) {
    done = false;
    vector<string> vectorofStrings;
    //vectorofStrings = Lexer::lexer(argv[1]);
    vectorofStrings = Lexer::lexer("fly.txt");
    Parser::parse(vectorofStrings);
    done = true;
    close(client_socket);
    return 0;
}