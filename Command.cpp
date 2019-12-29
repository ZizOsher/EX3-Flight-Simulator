#include "CommandMap.h"
#include "Commands.h"
#include <thread>
using namespace std;

typedef struct argsForOpenServerFnction{
}argsForServer;

void openServerToThread(){

    Server s;
    s.openServer();
}

int OpenServerCommand::exectue(itr itr1) {

    //send the funtion to thread
    thread t(openServerToThread);
    return 0;
};


int ConnectCommand::exectue(itr itr1) {

};
int DefineVarCommand::exectue(itr itr1) {

};



