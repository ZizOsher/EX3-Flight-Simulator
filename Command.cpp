#include "CommandMap.h"
#include "Command.h"

using namespace std;

void openServerToThread(){
    Server s;
    s.openServer();
}

int OpenServerCommand::execute(itr itr1) {
    //send the funtion to thre ad
     MyThread = new thread(openServerToThread);
    return 2;
};

void openClientThread(){
    Client c;
    c.openClient();
}

int ConnectCommand::execute(itr itr1) {
    clientThread = new thread(openClientThread);
};

void OpenServerCommand::joinThread() {
    if(MyThread->joinable()){
        MyThread->join();
    }
}

