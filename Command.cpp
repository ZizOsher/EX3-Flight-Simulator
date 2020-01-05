#include "CommandMap.h"
#include "Command.h"

using namespace std;
/*
typedef struct argsForOpenServerFnction{
}argsForServer;
*/

void openServerToThread(){
    Server s;
    s.openServer();
}

int openDateServer::execute(itr itr1) {
    //send the funtion to thre ad
     MyThread = new thread(openServerToThread);
    return 0;
};

void openClientThread(){
    Client c;
    c.openClient();
}

int ConnectCommand::execute(itr itr1) {
    clientThread = new thread(openClientThread);
};

int DefineVarCommand::execute(itr itr1) {

};

void openDateServer::joinThread() {
    if(MyThread->joinable()){
        MyThread->join();
    }
}

