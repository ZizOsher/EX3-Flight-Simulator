
#include "Commands.h"
#include "vector"
#include "unordered_map"
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


int ConccetCommand::exectue(itr itr1) {

};
int DefineVarCommanc::exectue(itr itr1) {

};



