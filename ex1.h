//
// Created by osher on 11/11/2019.
//

#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H
#include <map>
#include <string>
#include "Expression.h"
#include <list>
#include <stack>

using namespace std;

class Value : public Expression {
    double value;
    public:
        Value(double val) {
            this->value = val;
        }
        virtual double calculate();
        //virtual ~Value() {};
};

class Variable : public Expression {
    string name;
    double value;
    public:
        Variable(string n, double v) {
            this->name = n;
            this->value = v;
        }
        double calculate();
        Variable& operator++();
        Variable& operator--();
        Variable& operator+=(double d);
        Variable& operator-=(double d);
        Variable& operator++(int i);
        Variable& operator--(int i);
        //virtual ~Variable() {};
};

class UnaryOperator : public Expression {
    protected:
        Expression* exp;
    public:
        explicit UnaryOperator(Expression* ex) {
            this->exp = ex;
        }
        virtual double calculate() = 0;
        virtual ~UnaryOperator();
};

class UPlus : public UnaryOperator {
    public:
        explicit UPlus(Expression* ex) : UnaryOperator(ex) {}
        double calculate();
        virtual ~UPlus();
};

class UMinus : public UnaryOperator {
    public:
        explicit UMinus(Expression* ex) : UnaryOperator(ex) {}
        double calculate();
        virtual ~UMinus();
};

class BinaryOperator : public Expression {
    protected:
        Expression* left;
        Expression* right;
    public:
        BinaryOperator(Expression* l, Expression* r) {
            left = l;
            right = r;
        }
        virtual double calculate() = 0;
        virtual ~BinaryOperator();
};

class Plus : public BinaryOperator {
    public:
        Plus (Expression* l, Expression* r) : BinaryOperator(l,r) {}
        double calculate();
        virtual ~Plus();

};

class Minus : public BinaryOperator {
    public:
        Minus(Expression* l, Expression* r) : BinaryOperator(l,r) {}
        double calculate();
        virtual ~Minus();

};

class Div : public BinaryOperator {
    public:
        Div(Expression* l, Expression* r) : BinaryOperator(l,r) {}
        double calculate();
        virtual ~Div();

};

class Mul : public BinaryOperator {
    public:
        Mul(Expression* l, Expression* r) : BinaryOperator(l,r) {}
        double calculate();
        virtual ~Mul();

};

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

class ex1 {

};


#endif //UNTITLED_EX1_H
