
#ifndef UNTITLED1_OPENDATASERVER_H
#define UNTITLED1_OPENDATASERVER_H

#include <string>
#include <array>
#include <unordered_map>
#include <mutex>
using namespace std;


class Server {

private:
    int size = 200000;
    int Myclient_socket;
    bool isConnected = false;
    mutex mutex1;

    double infoInDoubleType;
    double arrayOfTokens[36];
    //unordered_map <string, double> mapForUpdateSimultorInfo;
public:
    int openServer();
    void splitAndPutIntoMap(int size, char* buffer) ;
    void readFromClient();

};


#endif //UNTITLED1_OPENDATASERVER_H
