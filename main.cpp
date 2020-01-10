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

#define PORT 8081

using namespace std;

int main(int argc, char const *argv[]) {
    vector<string> vectorofStrings;
    vectorofStrings = Lexer::lexer("fly.txt");
    Parser::parse(vectorofStrings);
    close(client_socket);
    return 0;


}


// test for server and client /////////////////////////////////
    // check the server
/*
    vector<string> vec = {"openDateServer", "5400"};
    openDateServer o;
    o.execute(vec.begin());
    o.joinThread();
/*
    // check the client
    Client client;
    client.openClient();
*/
////////////////////////////////////////////////////////////////////////////
