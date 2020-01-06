
#include "Server.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include <mutex>
#include <iostream>
#include <cstring>
#include "SimIncomingInfo.h"

#define PORT 5400
using namespace std;

int Server::openServer(itr itr1) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine

    int valPort = stoi(*itr1);
    address.sin_port = htons(valPort);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketfd, (struct sockaddr *) &address, &addrlen);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    cout << "client accecpted" << endl;
    Myclient_socket = client_socket;
    isConnected = true;
    readFromClient();
    return 1;
}

    //reading from client
void Server:: readFromClient(){
    char buffer[200000] = {0};
    // first get into the while, until reading ending reading from the simulator
    int valread = 0;
    // as long there is information from the simulator
    while (isConnected == true && valread!= -1){
        // lock the acess to the map
        mutex1.lock();
        int valread = read(Myclient_socket, buffer, size);
        splitAndPutIntoMap(size, buffer);

        // unlock the acess to the map
        mutex1.unlock();
        //cout << "ASDFGHJK" << endl;
    }

    std::cout<<buffer<<std::endl;

    close(Myclient_socket); //closing the listening socket
}
void Server::splitAndPutIntoMap(int size, char* buffer) {

    // collect chars
    string item = "";
    double val;
    double numforIndex36 = 0;
    unsigned int arrayIndex = 0;
    for(int i=0; i< size; i++){

        if(buffer[i] == '\n'){
            arrayOfTokens[arrayIndex]= val;
            break;
        }
        if (buffer[i] == ',' && item != "") {
            // convert from string to double
            val = stod(item);
            arrayOfTokens[arrayIndex]= val;
            arrayIndex++;
            item = "";
        //  if the char has value
        } else {
            item = item + buffer[i];
        }
    }

    SimIncomingInfo& mapForUpdateSimultorInfo = SimIncomingInfo::getInstance();

    mapForUpdateSimultorInfo.addValue("/instrumentation/airspeed-indicator/indicated-speed-kt", arrayOfTokens[0]);
    mapForUpdateSimultorInfo.addValue("/sim/time/warp", arrayOfTokens[1]);
    mapForUpdateSimultorInfo.addValue("/controls/switches/magnetos", arrayOfTokens[2]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/heading-indicator/offset-deg", arrayOfTokens[3]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/altimeter/indicated-altitude-ft", arrayOfTokens[4]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/altimeter/pressure-alt-ft", arrayOfTokens[5]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/attitude-indicator/indicated-pitch-deg", arrayOfTokens[6]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/attitude-indicator/indicated-roll-deg", arrayOfTokens[7]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/attitude-indicator/internal-pitch-deg", arrayOfTokens[8]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/attitude-indicator/internal-roll-deg", arrayOfTokens[9]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/encoder/indicated-altitude-ft", arrayOfTokens[10]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/encoder/pressure-alt-ft", arrayOfTokens[11]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/gps/indicated-altitude-ft", arrayOfTokens[12]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/gps/indicated-ground-speed-kt", arrayOfTokens[13]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/gps/indicated-vertical-speed", arrayOfTokens[14]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/heading-indicator/indicated-heading-deg", arrayOfTokens[15]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/magnetic-compass/indicated-heading-deg", arrayOfTokens[16]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/slip-skid-ball/indicated-slip-skid", arrayOfTokens[17]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/turn-indicator/indicated-turn-rate", arrayOfTokens[18]);
    mapForUpdateSimultorInfo.addValue("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", arrayOfTokens[19]);
    mapForUpdateSimultorInfo.addValue("/controls/flight/aileron", arrayOfTokens[20]);
    mapForUpdateSimultorInfo.addValue("/controls/flight/elevator", arrayOfTokens[21]);
    mapForUpdateSimultorInfo.addValue("/controls/flight/rudder", arrayOfTokens[22]);
    mapForUpdateSimultorInfo.addValue("/controls/flight/flaps", arrayOfTokens[23]);
    mapForUpdateSimultorInfo.addValue("/controls/engines/engine/throttle", arrayOfTokens[24]);
    mapForUpdateSimultorInfo.addValue("/controls/engines/current-engine/throttle", arrayOfTokens[25]);
    mapForUpdateSimultorInfo.addValue("/controls/switches/master-avionics", arrayOfTokens[26]);
    mapForUpdateSimultorInfo.addValue("/controls/switches/starter", arrayOfTokens[27]);
    mapForUpdateSimultorInfo.addValue("/engines/active-engine/auto-start", arrayOfTokens[28]);
    mapForUpdateSimultorInfo.addValue("/controls/flight/speedbrake", arrayOfTokens[29]);
    mapForUpdateSimultorInfo.addValue("/sim/model/c172p/brake-parking", arrayOfTokens[30]);
    mapForUpdateSimultorInfo.addValue("/controls/engines/engine/primer", arrayOfTokens[31]);
    mapForUpdateSimultorInfo.addValue("/controls/engines/current-engine/mixture", arrayOfTokens[32]);
    mapForUpdateSimultorInfo.addValue("/controls/switches/master-bat", arrayOfTokens[33]);
    mapForUpdateSimultorInfo.addValue("/controls/switches/master-alt", arrayOfTokens[34]);
    mapForUpdateSimultorInfo.addValue("/engines/engine/rpm", arrayOfTokens[35]);
}

/*
 *     // Splits str[] according to ','.
    // and returns next token.
    // It needs to be called
    // in a loop to get all tokens. It returns NULL
    // when there are no more tokens.
    int i=0;
    const char deli[2] = ",";
    // Retu // Splits str[] according to ','.
    // and returns next token.
    // It needs to be called
    // in a loop to get all tokens. It returns NULL
    // when there are no more tokens.
    int i=0;
    const crns first token
    char* token= strtok(buffer,deli);
    arrayOfTokens[i]= atof(token);

    // go over all the other tokens
    for(i=1; i<36; i++){
        printf("%s\n", token);
        // after it, put the token into the map in order

        // convert the token form string into double
        infoInDoubleType = atof(token);
        arrayOfTokens[i] = infoInDoubleType;

        //If you pass a NULL value, you are asking to
        // continue tokenizing the same string as before.
        token = strtok(NULL,deli);
    }
 */