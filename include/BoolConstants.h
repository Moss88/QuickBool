#ifndef BOOLCONSTANTS_H
#define BOOLCONSTANTS_H

#include <string>
#include "BoolBasicDefs.h"
#include "BoolType.h"

namespace QuickBool {

class BoolConstant : public BoolType {
public:
    bool isVar() const;
    bool isExpr() const;
    virtual std::string toString() const;
    virtual BoolValue value() const = 0;
    bool isAnd() const {
        return false;
    }
    virtual bool isOr() const {
        return false;
    }
    virtual bool isNot() const {
        return false;
    }

};

class BoolOne : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;
    bool isOne() const;
};

class BoolZero : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;
    bool isZero() const;
};

class BoolDontCare : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;
};

}
#endif // BOOLCONSTANTS_H

