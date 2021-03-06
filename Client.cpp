#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"
#include "Command.h"
#include "Interpreter.h"
#include <cmath>
#include <mutex>

using namespace std;
int client_socket;

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
    mutex1.lock();
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    mutex1.unlock();
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    return 0;
}

void Client::sendMessageToClient(string message) {
    // Send message to the server
    size_t is_sent = write(client_socket, message.c_str(), message.length());
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "'" << message << "'" << " sent to server" << std::endl;
    }
}
