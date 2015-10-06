#include "BoolBit.h"

BoolBit::BoolBit(std::shared_ptr<BoolBitShared> bb)
    : bb(bb) {}

bool BoolBit::isVar() const {
    return true;
}

bool BoolBit::isExpr() const {
    return false;
}

std::string BoolBit::toString() const {
    return bb->getName() + "[" + std::to_string(bb->getIndex()) + "]";
}

BoolValue BoolBit::value() const {
    return this->bb->value();
}

unsigned int BoolBit::getIndex() const {
    return this->bb->getIndex();
}

std::string BoolBit::getName() const {
    return this->bb->getName();
}

void BoolBit::setValue(BoolValue val) {
    this->bb->setVar(val);
}

BoolType* BoolBit::clone() const {
    return new BoolBit(this->bb);
}

/////////////////// BoolBitShared ///////////////////////////
BoolBitShared::BoolBitShared(std::string name, unsigned int index,
                             BoolValue val) :
                             val(val), idx(index), name(name)  {}

BoolBitShared::BoolBitShared(const BoolBitShared& other) {
    *this = other;
}


bool BoolBitShared::isVar() const {
    return true;
}

bool BoolBitShared::isExpr() const {
    return false;
}

std::string BoolBitShared::toString() const {
    return name + "[" + std::to_string(idx) + "]";
}

BoolValue BoolBitShared::value() const {
    return this->val;
}

unsigned int BoolBitShared::getIndex() const {
    return this->idx;
}

std::string BoolBitShared::getName() const {
    return this->name;
}

void BoolBitShared::setVar(BoolValue val) {
    this->val = val;
}

BoolType* BoolBitShared::clone() const {
    return new BoolBitShared(*this);
}
