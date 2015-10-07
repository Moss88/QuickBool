#ifndef BOOLBITVECTOR_H
#define BOOLBITVECTOR_H
#include <vector>
#include "BoolFunc.h"

class BoolFunc;
class BitVector {
public:
    BitVector() = default;
    BitVector(const std::vector<BoolFunc> &bits);
    BitVector(const std::vector<BoolFunc> &&bits);
    BoolFunc operator&(const BitVector& other)  const;
    BoolFunc operator|(const BitVector& other)  const;
    BoolFunc operator<(const BitVector& other)  const;
    BoolFunc operator<=(const BitVector& other) const;
    BoolFunc operator>(const BitVector& other)  const;
    BoolFunc operator>=(const BitVector& other) const;
    BoolFunc operator==(const BitVector& other) const;
    BoolFunc operator!=(const BitVector& other) const;

    std::vector<BoolFunc>::iterator begin();
    std::vector<BoolFunc>::iterator end();
    std::vector<BoolFunc>::const_iterator begin() const;
    std::vector<BoolFunc>::const_iterator end() const;
    unsigned int size() const;

private:
    std::vector<BoolFunc> bits;
};

#endif // BOOLBITVECTOR_H

