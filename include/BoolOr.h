#ifndef BOOLOR_H
#define BOOLOR_H
#include "BoolNaryExpr.h"
class BoolOr : public BoolNaryExpr {
public:
    BoolOr() = default;
    BoolOr(std::unique_ptr<BoolType> a, const BoolType &b);
    BoolOr(const BoolType& a, const BoolType& b);
    BoolOr(const BoolOr& other);
    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;
    bool isOr() const;

};

#endif // BOOLOR_H

