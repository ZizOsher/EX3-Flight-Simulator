//
// Created by hadar on 06/01/2020.
//

#include "Command.h"

void openClientThread(){
    Client c;
    c.openClient();
}

int ConnectCommand::execute(itr itr1) {
    clientThread = new thread(openClientThread);
};
