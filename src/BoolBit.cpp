#include "BoolBit.h"
BoolBit::BoolBit(std::string name, unsigned int index, BoolValue val)
    : val(val), idx(index), name(name) {}

bool BoolBit::isVar() const {
    return true;
}

bool BoolBit::isExpr() const {
    return true;
}

std::string BoolBit::toString() const {
    return name + "[" + std::to_string(idx) + "]";
}

BoolValue BoolBit::value() const {
    return this->val;
}

void BoolBit::setValue(BoolValue val) {
    this->val = val;
}
