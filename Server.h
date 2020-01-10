#ifndef UNTITLED1_OPENDATASERVER_H
#define UNTITLED1_OPENDATASERVER_H

#include <string>
#include <array>
#include <unordered_map>
#include <mutex>
#include "Command.h"

using namespace std;
extern bool done;

typedef vector<string>::iterator itr;

class Server {

private:
    int size = 200000;
    int Myclient_socket;
    bool isConnected = false;

    double infoInDoubleType;
    double arrayOfTokens[36];
    //unordered_map <string, double> mapForUpdateSimultorInfo;
public:
    int openServer(itr itr1);
    void splitAndPutIntoMap(int size, char* buffer) ;
    void readFromClient();

};


#endif //UNTITLED1_OPENDATASERVER_H
