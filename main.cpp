#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include "Server.h"
#include "Client.h"

#define PORT 8081

using namespace std;
int main(int argc, char const *argv[]){
    Server server;
    int serverNum = server.openServer();
    cout<< "serv11er "+serverNum<<endl;
    Client client;
    int clientNum = client.openClient();
    cout<< "clie11nt "+ clientNum<<endl;
}
