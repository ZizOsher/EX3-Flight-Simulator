//
// Created by hadar on 06/01/2020.
//

#include "Command.h"
#include "Client.h"
#include <thread>


void ConnectCommand::openClientThread(itr itr1) {
    Client c;
    c.openClient(itr1);
}

int ConnectCommand::execute(itr itr1) {
    clientThread = new thread(openClientThread,itr1);
    return this->getSteps();
}

int ConnectCommand::getSteps() {
    return this->steps;
};