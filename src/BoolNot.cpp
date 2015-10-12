#include "BoolNot.h"
#include "iostream"
using namespace std;
BoolNot::BoolNot(BoolType &a) {
    this->operands.push_back(std::unique_ptr<BoolType>(a.clone()));
}

BoolNot::BoolNot(const BoolNot& a) {
    this->operands.push_back(std::unique_ptr<BoolType>(a.operands.front()->clone()));
}


std::string BoolNot::toString() const {
    return "!(" + this->operands.front()->toString() +")";
}

BoolValue BoolNot::value() const {
    BoolValue val = this->operands.front()->value();
    if(val == BoolValue::One)
        return BoolValue::Zero;
    else if(val == BoolValue::Zero)
        return BoolValue::One;
    else
        return val;
}

bool BoolNot::isNot() const {
    return true;
}

BoolType* BoolNot::clone() const {
    return new BoolNot(*this);
}
