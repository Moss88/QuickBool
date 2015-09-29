#include "BoolManager.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

BoolFunc BoolManager::getBit(std::string name) {
    return BoolFunc(this->vars[KeyPair(name, 0)]);
}

BitVector BoolManager::getBitVector(std::string name, unsigned int size) {
    if(vars.find(KeyPair(name, 0)) != vars.end())
        throw std::runtime_error("BoolManager: Bit Vector Already Exists");
    vector<shared_ptr<BoolBit>> bits;
    for(unsigned int i = 0; i < size; i++)
        bits.push_back(this->vars[KeyPair(name, i)]);
    return BitVector(move(bits));
}

unsigned int BoolManager::numberVars() const {
    return this->vars.size();
}

