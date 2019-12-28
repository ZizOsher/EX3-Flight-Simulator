//
// Created by hadar on 24/12/2019.
//

#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#include <string>
using namespace std;


class Server {
    int Myclient_socket;
public:
    int openServer();
    string readFromClient();
};


#endif //UNTITLED1_SERVER_H
