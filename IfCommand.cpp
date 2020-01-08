#include "Command.h"
#include "Interpreter.h"
#include <bits/stdc++.h>

using namespace std;

int IfCommand::execute(itr itr1) {
  //  itr1++;
    resultBool = splitIntoTokens(*itr1);
    if (resultBool == true) {
            return 1;
    } else {
        return 0;
    }
}

bool IfCommand:: resultInBool(double result){
    if(result== 1){
        return true;
    }else{
        return false;
    }
}

bool  IfCommand:: splitIntoTokens(string str) {
    Expression *expressionLeft;
    Expression *expressionRight;
    Expression *expression;
    double result;
    bool boolResult;

    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(str);
    string intermediate;

    // Tokens by space' '
    while (getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    // Printing the token vector
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << '\n';
    }
    string operand = tokens[1];

    if(operand == "<") {

        // convert the string into expressions right and left
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);

       expression = new LessThan(expressionLeft,expressionRight);
       result = expression->calculate();
       boolResult = resultInBool(result);
       return boolResult;

    }if(operand == "<="){

        // convert the string into expressions right and left
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);

        expression = new NotGreaterThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;


    }if(operand == "=="){

        // convert the string into expressions right and left
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);

        expression = new Equal(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;


    }if(operand == "!="){

        // convert the string into expressions right and left
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);

        expression = new NotEqual(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;

    }if(operand == ">"){

        // convert the string into expressions right and left
        Interpreter::getInstance().setVariables("x=9");
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);
        expression = new GreaterThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;

    }if(operand == ">="){

        // convert the string into expressions right and left
        expressionLeft = Interpreter::getInstance().interpret(tokens[0]);
        expressionRight = Interpreter::getInstance().interpret(tokens[2]);

        expression = new NotLessThan(expressionLeft,expressionRight);
        result = expression->calculate();
        boolResult = resultInBool(result);
        return boolResult;

    }

for (int i = 0; i < tokens.size(); i++) {
        expression = Interpreter::getInstance().interpret(tokens[i]);
    }
}


