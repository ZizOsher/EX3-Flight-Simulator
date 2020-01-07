#ifndef UNTITLED1_CLIENT_H
#define UNTITLED1_CLIENT_H
#include <string>
#include "Command.h"

using namespace std;

class Client {

public:
    int openClient(itr index);
    //void sendMessage(int client_socket, string message); //int client_socket,
    static void sendMessageToClient(string message);
};


#endif //UNTITLED1_CLIENT_H
