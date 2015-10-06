#ifndef BOOLAND_H
#define BOOLAND_H
#include "BoolExpr.h"
class BoolAnd : public BoolExpr {
public:
    BoolAnd() = default;
    BoolAnd(const BoolType& a, const BoolType& b);
    BoolAnd(std::unique_ptr<BoolType> a, const BoolType& b);
    BoolAnd(const BoolAnd& other);

    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;

};

#endif // BOOLAND_H

