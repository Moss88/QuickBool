#include "BoolFunc.h"
#include "BoolConstants.h"
#include "BoolAnd.h"
#include "BoolOr.h"
#include "BoolNot.h"
#include <iostream>
using std::cout;
using std::endl;

using std::unique_ptr;

namespace QuickBool {
BoolFunc::BoolFunc(UBoolType val) : bValue(move(val)) {}

BoolFunc::BoolFunc(bool val) {
    if(val)
        bValue = std::unique_ptr<BoolOne>(new BoolOne());
    else
        bValue = std::unique_ptr<BoolZero>(new BoolZero());
}

BoolFunc::BoolFunc(const BoolFunc& func) {
    this->bValue = unique_ptr<BoolType>(func.bValue->clone());
}

BoolFunc::BoolFunc(BoolFunc&& func) {
    this->bValue = move(func.bValue);
}

BoolFunc::BoolFunc(const BoolType *pVal) {
    this->bValue = unique_ptr<BoolType>(pVal->clone());
}


BoolFunc BoolFunc::operator=(const BoolFunc& func) {
    if(this == &func)
        return *this;
    this->bValue = unique_ptr<BoolType>(func.bValue->clone());
    return *this;
}

BoolFunc& BoolFunc::operator=(BoolFunc&& func) {
    this->bValue = std::move(func.bValue);
    return *this;
}

BoolFunc& BoolFunc::operator&=(const BoolFunc& func) {
    if(func.get()->isOne())
        return *this;
    else if(this->get()->isOne())
    {
        *this = func;
        return *this;
    }
    else if(func.get()->isZero() || this->get()->isZero())
    {
        *this = BoolFunc(false);
        return *this;
    }
    unique_ptr<BoolAnd> newFunc = unique_ptr<BoolAnd>(new BoolAnd(std::move(this->bValue), *func.bValue));
    this->bValue = move(newFunc);
    return *this;
}

BoolFunc& BoolFunc::operator&=(BoolFunc&& func) {
    if(func.get()->isOne())
        return *this;
    else if(this->get()->isOne())
    {
        this->bValue = std::move(func.bValue);
        return *this;
    }
    else if(func.get()->isZero() || this->get()->isZero())
    {
        *this = BoolFunc(false);
        return *this;
    }
    
    this->bValue = unique_ptr<BoolAnd>(new BoolAnd(std::move(this->bValue), std::move(func.bValue)));
    return *this;
}



BoolFunc BoolFunc::operator&(const BoolFunc& other) const {
    if(other.get()->isOne())
        return *this;
    else if(this->get()->isOne())
        return other;
    else if(other.get()->isZero() | this->get()->isZero())
        return BoolFunc(false);
    return BoolFunc(unique_ptr<BoolAnd>(new BoolAnd(*this->bValue, *other.bValue)));
}

BoolFunc BoolFunc::operator|=(const BoolFunc& func) {
    if(func.get()->isZero())
        return *this;
    else if(this->get()->isZero())
    {
        *this = func;
        return *this;
    }
    else if(func.get()->isOne() | this->get()->isOne())
        return BoolFunc(true);

    unique_ptr<BoolOr> newFunc = unique_ptr<BoolOr>(new BoolOr(std::move(this->bValue), *func.bValue));
    this->bValue = move(newFunc);
    return *this;
}

BoolFunc BoolFunc::operator|=(const BoolType& func) {
    if(func.isZero())
        return *this;
    else if(this->get()->isZero())
    {
        *this = BoolFunc(&func);
        return *this;
    }
    else if(func.isOne() | this->get()->isOne())
        return BoolFunc(true);

    unique_ptr<BoolOr> newFunc = unique_ptr<BoolOr>(new BoolOr(std::move(this->bValue), func));
    this->bValue = move(newFunc);
    return *this;
}

BoolFunc BoolFunc::operator|(const BoolFunc& other) const {
    if(other.get()->isZero())
        return *this;
    else if(this->get()->isZero())
        return other;
    else if(other.get()->isOne() | this->get()->isOne())
        return BoolFunc(true);
    return BoolFunc(unique_ptr<BoolOr>(new BoolOr(*this->bValue, *other.bValue)));
}

BoolFunc BoolFunc::operator|(const BoolType& other) const {
    if(other.isZero())
        return *this;
    //else if(this->get()->isZero())
    //    return BoolFunc(&other);
    else if(other.isOne() | this->get()->isOne())
        return BoolFunc(true);
    return BoolFunc(unique_ptr<BoolOr>(new BoolOr(*this->bValue, other)));
}


BoolFunc BoolFunc::operator!() const {
    if(this->get()->isZero())
        return BoolFunc(true);
    else if(this->get()->isOne())
        return BoolFunc(false);
    else if(this->get()->isNot())
        return BoolFunc(unique_ptr<BoolType>(static_cast<const BoolNot*>(this->get())->begin()->get()->clone()));

    return BoolFunc(unique_ptr<BoolNot>(new BoolNot(*this->bValue)));
}

const BoolType* BoolFunc::get() const {
    return this->bValue.get();
}

BoolType* BoolFunc::get() {
    return this->bValue.get();
}

std::string BoolFunc::toString() const {
    return this->bValue->toString();
}

BoolValue BoolFunc::evaluate() const {
    return this->bValue->value();
}

bool BoolFunc::isExpr() const {
    return this->bValue->isExpr();
}
bool BoolFunc::isVar() const {
    return this->bValue->isVar();
}

std::ostream& operator<<(std::ostream &stream, const BoolFunc& func) {
    stream << func.toString();
    return stream;
}

}
