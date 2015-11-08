#ifndef BOOLTYPE_H
#define BOOLTYPE_H
#include <string>
#include "BoolBasicDefs.h"

namespace QuickBool { 
class BoolType {
public:
    virtual BoolType* clone() const = 0;
    virtual std::string toString() const = 0;
    virtual BoolValue value() const = 0;

    virtual bool isVar() const {
        return false;
    }

    virtual bool isExpr() const {
        return false;
    }
    virtual bool isAnd() const {
        return false;
    }
    virtual bool isOr() const {
        return false;
    }
    virtual bool isNot() const {
        return false;
    }

    virtual bool isOne() const {
        return false;
    }

    virtual bool isZero() const {
        return false;
    }

protected:
    friend std::ostream& operator<< (std::ostream& outStream, const BoolType& val);

};


}

#endif // BOOLTYPE_H

