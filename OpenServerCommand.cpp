//
// Created by hadar on 06/01/2020.
//

#include <iostream>
#include "Command.h"
using namespace std;


void OpenServerCommand::openServerToThread(itr itr1) {
    Server s;
    s.openServer(itr1);
}

int OpenServerCommand::execute(itr itr1) {
    //send the function to thread
    itr1++;
    MyThread = new thread(openServerToThread,itr1);

    return 2;
}

void OpenServerCommand::joinThread() {
    if(MyThread->joinable()){
        MyThread->join();
    }
}