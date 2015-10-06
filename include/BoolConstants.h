#ifndef BOOLCONSTANTS_H
#define BOOLCONSTANTS_H

#include <string>
#include "BoolBasicDefs.h"
#include "BoolType.h"
class BoolConstant : public BoolType {
public:
    bool isVar() const;
    bool isExpr() const;
    virtual std::string toString() const;
    virtual BoolValue value() const = 0;
};

class BoolOne : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;
};

class BoolZero : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;

};

class BoolDontCare : public BoolConstant {
public:
    BoolValue value() const;
    BoolType* clone() const;

};
#endif // BOOLCONSTANTS_H

