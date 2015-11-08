#include "BitVector.h"
#include "BoolFunc.h"
#include "BoolAlgorithms.h"
#include <iostream>
using std::cout;
using std::endl;
using std::move;
namespace QuickBool {
void sizeExcept(const BitVector& a, const BitVector& b){
    if(a.size() != b.size())
        throw std::runtime_error("BitVector: bitvectors do not match " +
                                 std::to_string(a.size()) + " and " +
                                 std::to_string(b.size()));
}

BitVector::BitVector(const std::vector<BoolFunc> &bits) {
    this->bits.insert(this->bits.end(), bits.begin(), bits.end());
}

BitVector::BitVector(const std::vector<BoolFunc> &&bits) {
    this->bits = move(bits);
}


BoolFunc BitVector::operator<(const BitVector& other) const {
    sizeExcept(*this, other);

    // Perform Algorithm
    int i;
    BoolFunc x;
    BoolFunc func;
    bool xSet = false;
    for(i = this->size() - 1; i >= 0; i--)
    {
        // Generate term = ~AB;
        BoolFunc term = !bits[i] & other.bits[i];

        // Generate X
        BoolFunc eq1 =  bits[i] & other.bits[i];
        BoolFunc eq2 =  (!bits[i]) & (!other.bits[i]);

        if(xSet)
        {
            // Use Old X Term
            func |= term & x;
            x = x & (eq1 | eq2);
        }
        else
        {
            x = eq1 | eq2;
            func = term;
            xSet = true;
        }
    }
    return move(func);
}

BoolFunc BitVector::operator<=(const BitVector& other) const {
    BoolFunc func = (*this < other) | (*this == other);
    return move(func);
}

BoolFunc BitVector::operator>(const BitVector& other)  const {
    return move(other < *this);
}

BoolFunc BitVector::operator>=(const BitVector& other) const {
    return move(other <= *this);
}

BoolFunc BitVector::operator==(const BitVector& other) const {
    BoolFunc func(true);
    sizeExcept(*this, other);
    auto otherIter = other.begin();
    for(auto thisIter = begin(); thisIter != end(); thisIter++, otherIter++)
        func &= ((*thisIter) & (*otherIter)) | ((!*thisIter) & (!*otherIter));
    return func;
}

BoolFunc BitVector::operator!=(const BitVector& other) const {
    return move(!(*this == other));
}

std::vector<BoolFunc>::iterator BitVector::begin() {
    return bits.begin();
}

std::vector<BoolFunc>::iterator BitVector::end() {
    return bits.end();
}

std::vector<BoolFunc>::const_iterator BitVector::begin() const {
    return this->bits.cbegin();
}
std::vector<BoolFunc>::const_iterator BitVector::end() const {
    return this->bits.cend();
}

unsigned int BitVector::size() const {
    return bits.size();
}

}
