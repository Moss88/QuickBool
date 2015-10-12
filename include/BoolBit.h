#ifndef BOOLBIT_H
#define BOOLBIT_H
#include <string>
#include "BoolType.h"


class BoolBitShared : public BoolType {
public:
    BoolBitShared(std::string name, unsigned int index = 0,
            BoolValue val = BoolValue::Unknown);
    BoolBitShared(const BoolBitShared& other);
    virtual bool isVar() const;
    virtual std::string toString() const;
    virtual BoolValue value() const;
    unsigned int getIndex() const;
    std::string getName() const;
    void setVar(BoolValue val);
    BoolType* clone() const;

private:
    BoolValue val = BoolValue::Unknown;
    unsigned int idx = 0;
    unsigned int id = 0;
    std::string name = "";
};

class BoolBit : public BoolType {
public:
    BoolBit(std::shared_ptr<BoolBitShared> bb);
    void setValue(BoolValue val);
    bool isVar() const;
    std::string toString() const;
    BoolValue value() const;
    BoolType* clone() const;
    unsigned int getIndex() const;
    std::string getName() const;
private:
    std::shared_ptr<BoolBitShared> bb;
};


#endif // BOOLBIT_H

