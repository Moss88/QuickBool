#ifndef BOOLNARYEXPR_H
#define BOOLNARYEXPR_H
#include "BoolExpr.h"

class BoolFunc;
class BoolNaryExpr : public BoolExpr {
public:
    void addOperand(const BoolType& func);
    void addOperand(BoolType&& func);

};







#endif // BOOLNARYEXPR_H

