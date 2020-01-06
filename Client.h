//
// Created by hadar on 24/12/2019.
//
#ifndef UNTITLED1_CLIENT_H
#define UNTITLED1_CLIENT_H
#include <string>
using namespace std;

class Client {
public:
    int openClient();
    void sendMessage(int client_socket, string messeage);
};


#endif //UNTITLED1_CLIENT_H
