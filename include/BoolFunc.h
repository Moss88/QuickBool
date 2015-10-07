#ifndef BOOLFUNC_H
#define BOOLFUNC_H
#include "BoolBasicDefs.h"
#include "BoolType.h"

class BoolFunc {
public:
    BoolFunc() = default;
    BoolFunc(std::unique_ptr<BoolType> pVal);
    BoolFunc(bool val);
    BoolFunc(const BoolFunc& func);
    BoolFunc(BoolFunc&& func);

    // TODO implement move functionality to save performance
    // right now operations are very inefficent
    BoolFunc operator=(const BoolFunc& func);
    BoolFunc operator=(BoolFunc&& func);

    BoolFunc operator&=(const BoolFunc& func);
    BoolFunc operator&=(const BoolType& func) const;
    BoolFunc operator&(const BoolFunc& func) const;
    BoolFunc operator&(const BoolType& func) const;
    BoolFunc operator|(const BoolFunc& func) const;
    BoolFunc operator|=(const BoolFunc& func);

    BoolFunc operator!() const;
    BoolValue evaluate() const;
    const BoolType* get() const;
    BoolType* get();
    std::string toString() const;

private:
    UBoolType bValue;
};
/*
BoolFunc operator!(const BoolBit& a);
BoolFunc operator|(const BoolBit& a, const BoolBit& b);
BoolFunc operator&(const BoolBit& a, const BoolBit& b);
*/
#endif // BOOLFUNC_H

