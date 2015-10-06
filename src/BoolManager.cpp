#include "BoolManager.h"
#include "BoolBit.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;

BoolFunc BoolManager::getBit(std::string name, int idx) {
    auto iter = vars.find(KeyPair(name, idx));
    if(iter == vars.end())
    {
        shared_ptr<BoolBitShared> sbb = shared_ptr<BoolBitShared>(new BoolBitShared(name, idx));
        this->vars[BoolManager::KeyPair(name, idx)] = sbb;
        return BoolFunc(unique_ptr<BoolBit>(new BoolBit(sbb)));
    }
    return BoolFunc(unique_ptr<BoolBit>(new BoolBit(iter->second)));
}

BitVector BoolManager::getBitVector(std::string name, unsigned int size) {
    if(vars.find(KeyPair(name, 0)) != vars.end())
        throw std::runtime_error("BoolManager: Bit Vector Already Exists");
    vector<BoolFunc> bits;
    for(unsigned int i = 0; i < size; i++)
        bits.push_back(BoolFunc(unique_ptr<BoolBit>(new BoolBit(this->vars[BoolManager::KeyPair(name, i)]))));
    return BitVector(move(bits));
}

unsigned int BoolManager::numberVars() const {
    return this->vars.size();
}

void BoolManager::setValue(BoolValue val, std::string name, int idx) {
    this->vars[BoolManager::KeyPair(name, idx)]->setVar(val);
}

