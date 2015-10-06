#ifndef BOOLNOT_H
#define BOOLNOT_H
#include "BoolExpr.h"
class BoolNot : public BoolExpr {
public:
    BoolNot() = default;
    BoolNot(BoolType& a);
    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;
};

#endif // BOOLNOT_H

