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

int OpenServerCommand::execute(itr itr1) {
    //send the funtion to thre ad
     MyThread = new thread(openServerToThread);
    return 2;
};

int ConnectCommand::execute(itr itr1) {

};

void OpenServerCommand::joinThread() {
    if(MyThread->joinable()){
        MyThread->join();
    }
}
