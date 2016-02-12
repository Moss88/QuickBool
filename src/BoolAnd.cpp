#include "BoolAnd.h"
#include <iostream>
namespace QuickBool {
using std::unique_ptr;

BoolAnd::BoolAnd(unique_ptr<BoolType> a, unique_ptr<BoolType> b) {       
    if(a.get()->isAnd())
    {
        BoolAnd* andPtr = static_cast<BoolAnd*>(a.get());
        this->operands = std::move(andPtr->operands);
    }
    else
        this->operands.push_back(move(a));

    if(b->isAnd())
    {
        BoolAnd* ptr = static_cast<BoolAnd*>(b.get());
        std::move(ptr->operands.begin(), ptr->operands.end(), std::back_inserter(this->operands));
    }
    else
        this->operands.emplace_back(move(b));
}



BoolAnd::BoolAnd(unique_ptr<BoolType> a, const BoolType &b) {       
    if(a.get()->isAnd())
    {
        BoolAnd* andPtr = static_cast<BoolAnd*>(a.get());
        this->operands = std::move(andPtr->operands);
    }
    else
        this->operands.push_back(move(a));

    if(b.isAnd())
    {
        const BoolAnd* ptr = static_cast<const BoolAnd*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolAnd::BoolAnd(const BoolType &a, const BoolType &b) {
    if(a.isAnd())
    {
        const BoolAnd* ptr = static_cast<const BoolAnd*>(&a);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(a.clone()));

    if(b.isAnd())
    {
        const BoolAnd* ptr = static_cast<const BoolAnd*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<BoolType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<BoolType>(b.clone()));
}

BoolAnd::BoolAnd(const BoolAnd& other) {
    for(auto &op:other.operands)
        this->operands.push_back(unique_ptr<BoolType>(op->clone()));
}

std::string BoolAnd::toString() const {
    std::string str = "(";
    auto lastPos = operands.cend() - 1;
    for(auto iter = operands.cbegin(); iter != operands.cend(); ++iter)
    {
        str += (*iter)->toString();
        if(iter != lastPos)
            str += " & ";
    }
    return str + ")";
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

bool BoolAnd::isAnd() const {
    return true;
}


BoolType* BoolAnd::clone() const {
    return new BoolAnd(*this);
}


}
