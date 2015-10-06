#include "BoolNot.h"

BoolNot::BoolNot(BoolType &a) {
    this->operands.push_back(std::unique_ptr<BoolType>(a.clone()));
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

BoolType* BoolNot::clone() const {
    return nullptr; //new BoolNot(*this);
}
