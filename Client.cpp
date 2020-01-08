#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "Client.h"
#include "Command.h"
#include "Interpreter.h"
#include <cmath>

using namespace std;
int client_socket;
#define PORT 5402

int Client::openClient(itr index) {
    //create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    index++;
    string ipAddress = *index;
    // Removing '"' from both ends of ip
    size_t pos = ipAddress.size() - 1;
    ipAddress = ipAddress.substr(1, pos - 1);
    const char* ip = ipAddress.c_str();

    index++;
    Interpreter& i = Interpreter::getInstance();
    int valPort = round(i.interpret(*index)->calculate());

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(valPort);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    cout << client_socket << endl;
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    //close(client_socket);
    return 0;
}

/*
void Client::sendMessage(int client_socket, string message) { //
    //if here we made a connection
    //string message = "set " + path+ " " + to_string(value) + "\r\n";
    message = "set controls/flight/rudder -1\r\n";

    // Send message to the server
   int is_sent = write(client_socket, message.c_str(), message.length());
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "'" << message << "'" << " sent to server" << std::endl;
    }
}
*/

void Client::sendMessageToClient(string message) {
    //message = message + "\r\n";
    // Send message to the server
    //cout << "I hope the someone gets my" << endl;
    int is_sent = write(client_socket, message.c_str(), message.length());
    //cout << "Sabich shel Ovad" << endl;
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "'" << message << "'" << " sent to server" << std::endl;
    }
}
