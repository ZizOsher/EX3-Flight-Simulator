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

#define PORT 8081

using namespace std;

int main(int argc, char const *argv[]) {
    vector<string> vectorofStrings;
    vectorofStrings = Lexer::lexer("fly.txt");
    Parser::parse(vectorofStrings);
}