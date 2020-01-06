#include "Expressions.h"
#include <list>
#include "SimIncomingInfo.h"

using namespace std;

double Value::calculate() {
    return this->value;
}

double Variable::calculate() {
    if ((!this->simBindOut) && (this->sim != "")) {
        this->value = SimIncomingInfo::getInstance().getValue(this->sim);
    }
    return this->value;
}

Variable& Variable::operator++() {
    ++this->value;
    return *this;
}

Variable& Variable::operator--() {
    --this->value;
    return *this;
}

Variable& Variable::operator+=(double d) {
    this->value += d;
    return *this;
}

Variable& Variable::operator-=(double d) {
    this->value -= d;
    return *this;
}

Variable& Variable::operator++(int i) {
    this->value++;
    return *this;
}

Variable& Variable::operator--(int i) {
    this->value--;
    return *this;
}

void Variable::setValue(double d) {
    this->value = d;
}

/*
Variable &Variable::operator=(double d) {
    this->value = d;
    return *this;
}
 */

UnaryOperator::~UnaryOperator() {
    //delete this->exp;
}

double UPlus::calculate() {
    return this->exp->calculate();
}

UPlus::~UPlus() {
    delete this->exp;
}

double UMinus::calculate() {
    return ((-1) * (this->exp->calculate()));
}

UMinus::~UMinus() {
    delete this->exp;
}

BinaryOperator::~BinaryOperator() {}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}

Plus::~Plus() {
    delete this->left;
    delete this->right;
}

double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}

Minus::~Minus() {
    delete this->left;
    delete this->right;
}

double Div::calculate() {
    try {
        double r = this->right->calculate();
        if (r == 0) {
            throw "Zero division is not defined.";
        } else {
            return this->left->calculate() / r;
        }
    } catch(const char &e) {
        throw e;
    }
}

Div::~Div() {
    delete this->left;
    delete this->right;
}

double Mul::calculate() {
    return (this->left->calculate() * this->right->calculate());
}

Mul::~Mul() {
    delete this->left;
    delete this->right;
}