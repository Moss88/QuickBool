#ifndef BOOLEXPR_H
#define BOOLEXPR_H
#include <vector>
#include "BoolType.h"

class BoolExpr : public BoolType {

    virtual std::vector<BoolType>::iterator begin() {
        return operands.begin();
    }

    virtual std::vector<BoolType>::iterator end() {
        return operands.end();
    }

    virtual unsigned int size() const {
        return operands.size();
    }

    constexpr bool isVar() const {
        return false;
    }

    constexpr bool isExpr() const {
        return true;
    }

private:
    std::vector<BoolType> operands;
};



#endif // BOOLEXPR_H

