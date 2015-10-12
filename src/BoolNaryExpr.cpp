#include "BoolNaryExpr.h"
#include "BoolFunc.h"

void BoolNaryExpr::addOperand(const BoolType& func) {
    this->operands.push_back(std::unique_ptr<BoolType>(func.clone()));
}

