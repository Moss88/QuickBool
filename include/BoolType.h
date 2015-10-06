#ifndef BOOLTYPE_H
#define BOOLTYPE_H
#include <string>
#include "BoolBasicDefs.h"
class BoolType {
public:
    virtual bool isVar() const = 0;
    virtual bool isExpr() const = 0;
    virtual BoolType* clone() const = 0;
    virtual std::string toString() const = 0;
    virtual BoolValue value() const = 0;
protected:
    friend std::ostream& operator<< (std::ostream& outStream, const BoolType& val);

};




#endif // BOOLTYPE_H

