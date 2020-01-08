#ifndef UNTITLED1_INTERPRETER_H
#define UNTITLED1_INTERPRETER_H
#include <map>
#include <string>
#include "Expressions.h"
#include <list>
#include <stack>
#include "SymbolTable.h"

using namespace std;

/**
 * this class interprets expressions and evalutes them.
 */
class Interpreter {
    string operators = "-+*/";
    map<string, int> precedenceMap;
    string functions[2] = {"(+(", "(-("};
    map<string, double> setVarsMap;
    SymbolTable& SymTable = SymbolTable::getInstance();
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
    bool interpretCondition(string str);
    Expression* ShuntingYard(const string& inputToParse);
    string findNumInStr(string s, int index);
    string findVarInStr(string s, int index);
    bool isFunc(string f);
    void setVariables(const string &s);
    bool isaNumber(const string &str);
    //bool isaVariable(const string &str);
    Interpreter(Interpreter const&) = delete;
    // in = we create a new copy of the map;
    void operator= (Interpreter const&) = delete;
    static Interpreter& getInstance();
    virtual ~Interpreter();

    static string removeAllWhiteSpaces(string input);
};
#endif //UNTITLED1_INTERPRETER_H
