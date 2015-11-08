#ifndef BOOLNOT_H
#define BOOLNOT_H
#include "BoolExpr.h"

namespace QuickBool {

class BoolNot : public BoolExpr {
public:
    BoolNot() = default;
    BoolNot(const BoolNot &a);
    BoolNot(BoolType& a);
    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;
    bool isNot() const;

};

}
#endif // BOOLNOT_H

