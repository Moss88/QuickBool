#include "BoolOr.h"

using std::unique_ptr;
BoolOr::BoolOr(unique_ptr<BoolType> a, const BoolType &b) {
    this->operands.push_back(move(a));
    this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolOr::BoolOr(const BoolType& a, const BoolType& b) {
    this->operands.push_back(unique_ptr<BoolType>(a.clone()));
    this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolOr::BoolOr(const BoolOr& other) {
    for(auto &op:other.operands)
        this->operands.push_back(unique_ptr<BoolType>(op->clone()));
}


std::string BoolOr::toString() const {
    return "(" + operands.front()->toString() + " | " +
                 operands.back()->toString() + ")";
}

BoolValue BoolOr::value() const {
    bool hasDontCare = false;
    for(auto &op:operands)
    {
        if(op->value() == BoolValue::One)
            return BoolValue::One;
        else if(op->value() == BoolValue::DontCare)
            hasDontCare = true;
    }
    if(hasDontCare)
        return BoolValue::DontCare;
    return BoolValue::Zero;
}

BoolType* BoolOr::clone() const {
    return new BoolOr(*this);
}
