#ifndef BOOLBITVECTOR_H
#define BOOLBITVECTOR_H
#include <vector>
#include "BoolBit.h"

class BitVector {
public:
    BitVector() = default;
    BitVector(std::vector<std::shared_ptr<BoolBit>> bits);
private:
    std::vector<BoolBit> bits;
};

#endif // BOOLBITVECTOR_H

