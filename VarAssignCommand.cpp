#include "Command.h"
#include "Expressions.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include "Client.h"
using namespace std;

/**
 * while we haven't reached a newline character, keep concatenating itr1 to one string which will be
 * sent to interpretation. If the item reached is a variable it is passed to the func setVaraibles (taking the
 * variable's binding into account).
 * Finally, the variable will be assigned the value calculated by the interpreter.
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
        itr1++;
        Interpreter& i = Interpreter::getInstance();
        string res;
        while (*itr1 != "\n") {
            if (SymTable.getVariable(*itr1)) {
                string setVarStr;
                setVarStr = *itr1 + "=" + to_string(SymTable.getVariable(*itr1)->calculate());
            }

            //TODO: while we haven't reached a newline character, keep concatenating itr1 to one string which will be
            // sent to interpretation. If the item reached is a variable it is passed to the func setVariables (take
            // binding into account).
            // Finally, the variable will be assigned the calculated value.

        }
    } else {
        string message = "The variable '" + subjectName + "' is not defined.";
        throw message;
    }
    return cnt;
}