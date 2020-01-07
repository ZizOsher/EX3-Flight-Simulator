#include "Command.h"
#include "Expressions.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include "Client.h"
using namespace std;

/**
 * Auxiliary function that matches the correct operator to a variable based on the string oper.
 *
 * @param v
 * @param val
 * @param oper
*/
void matchOperator(Variable* v, double val, string oper) {
    if (oper == "=") {
        v->setValue(val);
    } else if (oper == "+=") {
        v->setValue(v->calculate() + val);
    } else if (oper == "-=") {
        v->setValue(v->calculate() - val);
    }
}

/**
 * This function interprets and calculates the value of and expression to be assigned to the variable using the
 * interpreter. The variable will be assigned the value calculated by the interpreter , and if the variable is
 * outwards bound, a "set" command is sent to the simulator.
 * @param itr1
 * @return cnt
 */
int VarAssignCommand::execute(itr itr1) {
    unsigned int cnt = 0;
    SymbolTable& SymTable = SymbolTable::getInstance();
    string subjectName = *itr1;
    itr1++;
    string opr = *itr1;
    if (SymTable.isInMap(subjectName)) {
        Variable* subjectVariable = SymTable.getVariable(subjectName);
        itr1++;
        Interpreter& i = Interpreter::getInstance();
        double valToAssign;
        valToAssign = i.interpret(*itr1)->calculate();
        if (subjectVariable->isBoundOut()) {
            string message = "set " + subjectVariable->getSim() + " " + to_string(valToAssign);
            Client::sendMessageToClient(message);
        }
        matchOperator(subjectVariable, valToAssign, opr);
    } else {
        string message = "The variable '" + subjectName + "' is not defined.";
        throw message;
    }
    return 3;
}