#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H
#include <map>
#include <string>
#include "Expressions.h"
#include <list>
#include <stack>

using namespace std;
/**
 * Expression Interface
 */
class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

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
	string sim;
	bool simBindOut;
    public:
        Variable(string n, double v) {
            this->name = n;
            this->value = v;
        }
		Variable(string n, double v, string si, bool sbo) {
            this->name = n;
            this->value = v;
			this->sim = si;
			this->simBindOut = sbo;
        }
        Variable(string n, string si, bool sbo) {
            this->name = n;
            this->sim = si;
            this->simBindOut = sbo;
        }
        Variable(string n) {
            this->name = n;
        }
        double calculate();
        //Variable& operator=(double d);
        Variable& operator++();
        Variable& operator--();
        Variable& operator+=(double d);
        Variable& operator-=(double d);
        Variable& operator++(int i);
        Variable& operator--(int i);
        void setValue(double d);
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

/////////////////////////////////////////////////// add classes to the current project


class Equal : public BinaryOperator{
public:
    Equal(Expression* left, Expression* right): BinaryOperator(left, right){}
    double calculate();
    virtual  ~Equal();
};

class NotEqual : public BinaryOperator{
public:
    NotEqual(Expression* left, Expression* right):BinaryOperator(left,right){}
    double calculate();
    virtual ~NotEqual();
};

class NotGreaterThan : public BinaryOperator{
public:
    NotGreaterThan(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
    virtual ~NotGreaterThan();
};

class NotLessThan : public BinaryOperator{
public:
    NotLessThan(Expression* left, Expression *right):BinaryOperator(left, right){}
    double calculate();
    virtual ~NotLessThan();
};
class Greater : public BinaryOperator{
public:
    Greater(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
    virtual ~Greater();
};

class Lesser : public BinaryOperator{
public:
    Lesser(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
    virtual ~Lesser();
};

/*
class And:public BinaryOperator{
public:
    And(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
    virtual ~And();
};

class Or:public BinaryOperator{
public:
    Or(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
    virtual ~Or();
};
*/

#endif //UNTITLED_EX1_H