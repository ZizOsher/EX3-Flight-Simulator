//
// Created by hadar on 06/01/2020.
//

#include "Command.h"

void openServerToThread(){
    Server s;
    s.openServer();
}

int OpenServerCommand::execute(itr itr1) {
//send the funtion to thre ad
    MyThread = new thread(openServerToThread);
    return 0;
}

void OpenServerCommand::joinThread() {
    if(MyThread->joinable()){
        MyThread->join();
    }
}
