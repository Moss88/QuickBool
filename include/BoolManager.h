#ifndef BOOLMANAGER_H
#define BOOLMANAGER_H
#include <string>
#include <map>
#include <memory>
#include "BoolFunc.h"
#include "BitVector.h"
#include "BoolBit.h"


class BoolManager {
    struct KeyPair {
        KeyPair() = default;
        KeyPair(std::string name, unsigned int idx) : name(name), idx(idx) {}
        std::string name;
        int idx = 0;
        bool operator<(const KeyPair& other) const {
            return (this->name.compare(other.name) < 0) ||
                    ((this->name == other.name) && (this->idx < other.idx));
        }
    };

public:
    BoolManager() = default;
    BoolFunc getBit(std::string name, int idx = 0);
    BitVector getBitVector(std::string name, unsigned int size);
    void setValue(BoolValue val, std::string name, int idx = 0);
    unsigned int numberVars() const;
private:
    std::map<KeyPair, std::shared_ptr<BoolBitShared>> vars;
};

#endif // BOOLMANAGER_H

