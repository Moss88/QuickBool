#include "BitVector.h"
#include "BoolFunc.h"
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

/*
BoolFunc BitVector::operator&(const BitVector  other) const;
BoolFunc BitVector::operator|(const BitVector  other) const;
BoolFunc BitVector::operator<(const BitVector  other) const;
BoolFunc BitVector::operator<=(const BitVector other) const;
BoolFunc BitVector::operator>(const BitVector  other) const;
BoolFunc BitVector::operator>=(const BitVector other) const;
*/
BoolFunc BitVector::operator==(const BitVector other) const {
    BoolFunc func(true);
    sizeExcept(*this, other);
    auto otherIter = other.begin();
    for(auto thisIter = begin(); thisIter != end(); thisIter++, otherIter++)
        func &= ((*thisIter) & (*otherIter)) | ((!*thisIter) & (!*otherIter));
    return func;
}

BoolFunc BitVector::operator!=(const BitVector other) const {
    BoolFunc func(true);
    sizeExcept(*this, other);
    auto otherIter = other.begin();
    for(auto thisIter = begin(); thisIter != end(); thisIter++, otherIter++)
        func &= ((*thisIter) & (*otherIter)) | ((!*thisIter) & (!*otherIter));
    return func;
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
