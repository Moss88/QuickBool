#ifndef BOOLNARYEXPR_H
#define BOOLNARYEXPR_H
#include "BoolExpr.h"

namespace QuickBool {

class BoolFunc;
class BoolNaryExpr : public BoolExpr {
public:
    void addOperand(const BoolType& func);
    void addOperand(BoolType&& func);

};

}

#endif // BOOLNARYEXPR_H

