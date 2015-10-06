#include "BoolAnd.h"
using std::unique_ptr;

BoolAnd::BoolAnd(unique_ptr<BoolType> a, const BoolType &b) {
    this->operands.push_back(move(a));
    this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolAnd::BoolAnd(const BoolType &a, const BoolType &b) {
    this->operands.push_back(unique_ptr<BoolType>(a.clone()));
    this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolAnd::BoolAnd(const BoolAnd& other) {
    for(auto &op:other.operands)
        this->operands.push_back(unique_ptr<BoolType>(op->clone()));
}

std::string BoolAnd::toString() const {
    return "(" + operands.front()->toString() + " & "
            + operands.back()->toString() + ")";
}
BoolValue BoolAnd::value() const {
    bool hasDontCare = false;
    for(auto &op:operands)
    {
        if(op->value() == BoolValue::Zero)
            return BoolValue::Zero;
        else if(op->value() == BoolValue::DontCare)
            hasDontCare = true;
    }
    if(hasDontCare)
        return BoolValue::DontCare;
    return BoolValue::One;
}

BoolType* BoolAnd::clone() const {
    return new BoolAnd(*this);
}
