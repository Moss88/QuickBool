#ifndef BOOLEXPR_H
#define BOOLEXPR_H
#include <vector>
#include "BoolBasicDefs.h"
#include "BoolType.h"

namespace QuickBool {

class BoolExpr : public BoolType {
public:
    virtual std::vector<UBoolType>::iterator begin() {
        return operands.begin();
    }

    virtual std::vector<UBoolType>::iterator end() {
        return operands.end();
    }

    virtual std::vector<UBoolType>::const_iterator begin() const {
        return operands.begin();
    }

    virtual std::vector<UBoolType>::const_iterator end() const {
        return operands.end();
    }

    virtual unsigned int size() const {
        return operands.size();
    }

    bool isExpr() const {
        return true;
    }



protected:
    std::vector<UBoolType> operands;
};

}

#endif // BOOLEXPR_H

