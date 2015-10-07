#ifndef BOOLOR_H
#define BOOLOR_H
#include "BoolExpr.h"
class BoolOr : public BoolExpr {
public:
    BoolOr() = default;
    BoolOr(std::unique_ptr<BoolType> a, const BoolType &b);
    BoolOr(const BoolType& a, const BoolType& b);
    BoolOr(const BoolOr& other);
    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;

};

#endif // BOOLOR_H

