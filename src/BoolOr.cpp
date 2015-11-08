#include "BoolOr.h"
namespace QuickBool {
using std::unique_ptr;
BoolOr::BoolOr(unique_ptr<BoolType> a, const BoolType &b) {
    if(a.get()->isOr())
    {
        BoolOr* andPtr = static_cast<BoolOr*>(a.get());
        for(auto &op:*andPtr)
            this->operands.push_back(move(op));
    }
    else
        this->operands.push_back(move(a));

    if(b.isOr())
    {
        const BoolOr* ptr = static_cast<const BoolOr*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolOr::BoolOr(const BoolType& a, const BoolType& b) {
    if(a.isOr())
    {
        const BoolOr* ptr = static_cast<const BoolOr*>(&a);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(a.clone()));

    if(b.isOr())
    {
        const BoolOr* ptr = static_cast<const BoolOr*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolOr::BoolOr(const BoolOr& other) {
    for(auto &op:other.operands)
        this->operands.push_back(unique_ptr<BoolType>(op->clone()));
}


std::string BoolOr::toString() const {
    std::string str = "(";
    auto lastPos = operands.cend() - 1;
    for(auto iter = operands.cbegin(); iter != operands.cend(); ++iter)
    {
        str += (*iter)->toString();
        if(iter != lastPos)
            str += " | ";
    }
    return str + ")";
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

bool BoolOr::isOr() const {
    return true;
}


BoolType* BoolOr::clone() const {
    return new BoolOr(*this);
}
}
