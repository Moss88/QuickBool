#include "BoolManager.h"
#include "BoolBit.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
namespace QuickBool {
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
    vector<BoolFunc> bits;
    for(unsigned int i = 0; i < size; i++)
    {
        auto key = vars.find(KeyPair(name, i));
        if(key != vars.end())
            bits.push_back(BoolFunc(unique_ptr<BoolBit>(new BoolBit(key->second))));
        else
        {
            shared_ptr<BoolBitShared> sbb = std::make_shared<BoolBitShared>(BoolBitShared(name, i));
            this->vars[BoolManager::KeyPair(name, i)] = sbb;
            bits.push_back(BoolFunc(unique_ptr<BoolBit>(new BoolBit(sbb))));
        }
    }
    return BitVector(move(bits));
}

unsigned int BoolManager::numberVars() const {
    return this->vars.size();
}

void BoolManager::setValue(BoolValue val, std::string name, int idx) {
    this->vars[BoolManager::KeyPair(name, idx)]->setVar(val);
}
}
