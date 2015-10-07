#include "BoolConstants.h"
#include "BoolBasicDefs.h"
bool BoolConstant::isVar() const {
    return false;
}

bool BoolConstant::isExpr() const {
    return false;
}

std::string BoolConstant::toString() const {
    return to_string(this->value());
}

BoolValue BoolOne::value() const {
    return BoolValue::One;
}

BoolType* BoolOne::clone() const {
    return new BoolOne();
}

BoolValue BoolZero::value() const {
    return BoolValue::Zero;
}

BoolType* BoolZero::clone() const {
    return new BoolZero();
}

BoolValue BoolDontCare::value() const {
    return BoolValue::DontCare;
}

BoolType* BoolDontCare::clone() const {
    return new BoolDontCare();
}