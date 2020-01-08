#include "Expressions.h"
#include "Interpreter.h"
#include "Lexer.h"
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <stdexcept>
#include <vector>

Interpreter::~Interpreter() {}

Interpreter& Interpreter::getInstance() {
    static Interpreter oneInstance;
    return oneInstance;
}

string Interpreter::removeAllWhiteSpaces(string input) {
    list<string> v = Lexer::split(input, ' ', input.size());
    string res;
    for (string s : v) {
        res = res + s;
    }
    return res;
}

Expression* Interpreter::interpret(const string& inputToParse) {
    try {
        string in = Interpreter::removeAllWhiteSpaces(inputToParse);
        return ShuntingYard(in);
    } catch (const char &e) {
        throw e;
    }
}

Expression* Interpreter::ShuntingYard(const string& inputToParse) {
    stack<string> operatorStack;
    queue<string> outputQueue;
    int index = 0;
    while (index < inputToParse.size()) {
        char token;
        token = inputToParse[index];
        int skip = 1;
        // Check if number
        if (isdigit(token) != 0) {
            string num;
            num += findNumInStr(inputToParse, index);
            outputQueue.push(num);
            index += (num.length());
            continue;
            // Check if Variable
        } else if (isalpha(token) != 0) {
            string var;
            var += findVarInStr(inputToParse, index);
            outputQueue.push(var);
            index += (var.length());
            continue;
            // Check if operator
        } else if (this->operators.find(token) != string::npos) {
            string opr;
            if (token == '+') {
                if (index + 1 > inputToParse.size()) {      // Handles a binary operator at the end of the string.
                    throw "Invalid input.";
                } else if ((isalnum(inputToParse[index+1]) != 0 || inputToParse[index+1] == '(')
                           && inputToParse[index - 1] != '(') {    // Standard "+" operation
                    opr = "+";
                } else if (index == 0 && (operators.find(inputToParse[index + 1]) == string::npos)) {  // Unary operator (treated like a function)
                    opr = "(+(";
                } else if (inputToParse[index - 1] == '('
                           && (inputToParse[index + 1] == '(' || isdigit(inputToParse[index + 1]))) { // Also unary
                    opr = "(+(";
                    //skip = 2;
                } else {
                    throw "Invalid input.";
                }
            } else if (token == '-') {
                if (index + 1 > inputToParse.size()) {  // Handles a binary operator at the end of the input string.
                    throw "illegal math expression.";
                } else if (index == 0 && (operators.find(inputToParse[index + 1]) == string::npos)) { //unary minus
                    opr = "(-(";
                } else if (inputToParse[index - 1] == '(' && inputToParse[index + 1] == '(') { //unary minus
                    opr = "(-(";
                } else if (inputToParse[index - 1] == '(' && isdigit(inputToParse[index + 1])) { // a negative number
                    string num;
                    num += "-";
                    num += findNumInStr(inputToParse, index + 1);
                    outputQueue.push(num);
                    index += (num.length());
                    continue;
                } else if (((isalnum(inputToParse[index - 1])) || (inputToParse[index - 1] == ')'))
                           && ((isalnum(inputToParse[index + 1])) || (inputToParse[index + 1] == '('))) {
                    opr = "-";
                } else {
                    throw "illegal math expression.";
                }
            } else if (token == '*' || token == '/') {
                if ((isalnum(inputToParse[index + 1]) == 0) && inputToParse[index + 1] != '(') {
                    throw "illegal math expression.";
                } else if (index + 1 > inputToParse.size()) {  // Binary operator at the end of the input string.
                    throw "illegal math expression.";
                } else {
                    opr += token;
                }
            }
            // If the operator is a function (some form of unary operation)
            if (isFunc(opr)) {
                operatorStack.push(opr);
            } else {
                if (operatorStack.empty()) {
                    operatorStack.push(opr);
                } else {
                    while ((precedenceMap[operatorStack.top()] > precedenceMap[opr])
                           && (operatorStack.top() != "(")) {
                        string o1;
                        o1 += operatorStack.top();
                        outputQueue.push(o1);
                        operatorStack.pop();
                    }
                    operatorStack.push(opr);
                }
            }
        } else if (token == '(') {
            string t;
            t += token;
            operatorStack.push(t);

        } else if (token == ')') {
            while (operatorStack.top() != "(") {
                string o1;
                o1 += operatorStack.top();
                outputQueue.push(o1);
                operatorStack.pop();
            }
            if (operatorStack.top() == "(") {
                operatorStack.pop();
            }
        }
        index += skip;
    }
    while (!operatorStack.empty()) {
        string o1;
        o1 += operatorStack.top();
        outputQueue.push(o1);
        operatorStack.pop();
    }
    // Now, outputQueue is the postfix representation of the original infix input.
    stack<Expression*> resStack;
    while (!outputQueue.empty()) {
        string item;
        item = outputQueue.front();
        //cout << item << endl;
        outputQueue.pop();
        if (item.length() > 1 && (item[0] == '-' && isaNumber(item.substr(1, string::npos)))) {
            Value* ex = new Value((-1) * stod(item.substr(1)));
            resStack.push(ex);
        } else if (isaNumber(item)) {
            Value* ex = new Value(stod(item));
            resStack.push(ex);
        } else if (isalpha(item[0])) {
            try {
                /*
                 * double val;
                val = setVarsMap[item];
                Variable *ex = new Variable(item, val);
                resStack.push(ex);
                 */
                Variable *ex = SymTable.getVariable(item);
                resStack.push(ex);
            } catch (const char &e) {
                string message = "Variable: ";
                message += item;
                message+= " is not set. Can't interpret.";
                throw message;
            }
        }else {
            if (item == "(+(") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* ex = new UPlus(right);
                resStack.push(ex);
            } else if (item == "(-(") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* ex = new UMinus(right);
                resStack.push(ex);
            } else if (item == "+") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* left = resStack.top();
                resStack.pop();
                Expression* ex = new Plus(left, right);
                resStack.push(ex);
            } else if (item == "-") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* left = resStack.top();
                resStack.pop();
                Expression* ex = new Minus(left, right);
                resStack.push(ex);
            } else if (item == "*") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* left = resStack.top();
                resStack.pop();
                Expression* ex = new Mul(left, right);
                resStack.push(ex);
            } else if (item == "/") {
                Expression* right = resStack.top();
                resStack.pop();
                Expression* left = resStack.top();
                resStack.pop();
                Expression* ex = new Div(left, right);
                resStack.push(ex);
            }
        }
    }
    Expression* finalExpression = resStack.top();
    return finalExpression;
}

void Interpreter::setVariables(const string &s) {
    try {
        list<string> individualVars;
        int begin;
        begin = 0;
        for (int i = 0; i < s.length() + 1; i++) {
            if (s[i] == ';' || i + 1 == s.length()) {
                string varWithAssignment;
                if (i + 1 == s.length()) {
                    varWithAssignment = s.substr(begin, i + 1);
                } else {
                    varWithAssignment = s.substr(begin, i);
                }
                string name;
                name = findVarInStr(varWithAssignment, 0);
                string value;
                int equalsOperator;
                equalsOperator = varWithAssignment.find('=');
                try {
                    value = findNumInStr(varWithAssignment, equalsOperator + 1);
                } catch (const char &e) {
                    throw e;
                }
                double numericVal = stod(value);
                if (setVarsMap[name] != numericVal) {
                    setVarsMap.erase(name);
                }
                setVarsMap[name] = numericVal;
                begin = i + 1;
            }
        }
    } catch (const char &e) {
        throw e;
    }
}

bool Interpreter::isFunc(const string f) {
    for (int i = 0; i < 2; i++) {
        if (Interpreter::functions[i] == f) {
            return true;
        }
    }
    return false;
}

bool Interpreter::isaNumber(const string &str) {
    return str.find_first_not_of("0123456789.") == string::npos;
}

/**
 * This Method returns the number of indices in the input occupied by a number.
 * It also throws an exception if the input is bad.
 */
string Interpreter::findNumInStr(const string s, int index) {
    if (!isdigit(s[index])) {
        throw "Illegal input: a value given is not a valid number";
    }
    string result;
    result += s[index];
    for (int i = 1; i < s.length(); i++) {
        if (isdigit(s[index + i]) || s[index + i] == '.') {
            result += s[index + i];
        } else {
            break;
        }
    }
    if (result.find('.') != result.rfind('.')) {
        throw "Illegal input: a value given is not a valid number";
    }
    if (result.find('-') != result.rfind('-')) {
        throw "Illegal input: a value given is not a valid number";
    }
    return result;
}

/**
 * This Method returns the number of indices in the input occupied by a number.
 */
string Interpreter::findVarInStr(const string s, int index) {
    string result;
    result += s[index];
    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[index + i]) || s[index + i] == '_') {
            result += s[index + i];
        } else {
            break;
        }
    }
    return result;
}


bool resultInBool(double result){
    if(result== 1){
        return true;
    }else{
        return false;
    }
}

bool Interpreter::interpretCondition(string str) {
    Expression *expressionLeft;
    Expression *expressionRight;
    Expression *expression;
    double result;
    bool boolResult;

    string operatorsArray[6] = {"<", ">","<=", ">=", "==", "!="};
    // stringstream class check1
    string delimiter;
    int pos;
    int len;
    for (string op : operatorsArray) {
        if (str.find(op) != string::npos) {
            delimiter = op;
            pos = str.find(op);
            len = op.size();
            break;
        }
    }
    if (delimiter == "") {
        const char* e = "Illegal argument in conditional";
        throw e;
    }

    string tokens[3];
    tokens[0] = str.substr(0,pos);
    tokens[1] = str.substr(pos, len);
    tokens[2] = str.substr(pos + len, str.size() - (pos + len));

    string operand = tokens[1];

    // convert the string into expressions right and left
    expressionLeft = interpret(tokens[0]);
    expressionRight = interpret(tokens[2]);
    if(operand == "<") {
        expression = new LessThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    } else if(operand == "<=") {
        expression = new NotGreaterThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    }else if(operand == "==") {
        expression = new Equal(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    } else if(operand == "!=") {
        expression = new NotEqual(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    } else if(operand == ">") {
        expression = new GreaterThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    } else if(operand == ">=") {
        expression = new NotLessThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;
    }
}