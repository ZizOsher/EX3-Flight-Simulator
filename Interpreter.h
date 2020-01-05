#ifndef UNTITLED1_INTERPRETER_H
#define UNTITLED1_INTERPRETER_H
#include <map>
#include <string>
#include "Expressions.h"
#include <list>
#include <stack>

using namespace std;

/**
 * this class interprets expressions and evalutes them.
 */
class Interpreter {
    string operators = "-+*/";
    map<string, int> precedenceMap;
    string functions[2] = {"(+(", "(-("};
    map<string, double> setVarsMap;
public:
    Interpreter() {
        precedenceMap["+"] = 2;
        precedenceMap["-"] = 2;
        precedenceMap["*"] = 3;
        precedenceMap["/"] = 3;
        precedenceMap["(+("] = 4;
        precedenceMap["(-("] = 4;
    }
    Expression* interpret(const string& inputToParse);
    Expression* ShuntingYard(const string& inputToParse);
    string findNumInStr(string s, int index);
    string findVarInStr(string s, int index);
    bool isFunc(string f);
    void setVariables(const string &s);
    //void handleOperatorFromStack(stack<Expression*> res, const string &item);
    bool isaNumber(const string &str);
    //bool isaVariable(const string &str);
    virtual ~Interpreter();
};
#endif //UNTITLED1_INTERPRETER_H
