#ifndef BOOLEXPR_H
#define BOOLEXPR_H
#include <vector>
#include "BoolBasicDefs.h"
#include "BoolType.h"
class BoolExpr : public BoolType {

    virtual std::vector<UBoolType>::iterator begin() {
        return operands.begin();
    }

    virtual std::vector<UBoolType>::iterator end() {
        return operands.end();
    }

    virtual unsigned int size() const {
        return operands.size();
    }

    bool isVar() const {
        return false;
    }

    bool isExpr() const {
        return true;
    }

protected:
    std::vector<UBoolType> operands;
};



#endif // BOOLEXPR_H

