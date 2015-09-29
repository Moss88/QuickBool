#ifndef BOOLBIT_H
#define BOOLBIT_H
#include <string>
#include "BoolType.h"

class BoolBit : public BoolType {
public:
    BoolBit(std::string name, unsigned int index = 0,
            BoolValue val = BoolValue::Unknown);
    virtual void setValue(BoolValue val);
    virtual bool isVar() const;
    virtual bool isExpr() const;
    virtual std::string toString() const;
    virtual BoolValue value() const;
private:
    BoolValue val = BoolValue::Unknown;
    unsigned int idx = 0;
    unsigned int id = 0;
    std::string name = "";
};

#endif // BOOLBIT_H

