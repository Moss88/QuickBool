#ifndef BOOLMANAGER_H
#define BOOLMANAGER_H
#include <string>
#include <map>
#include <memory>
#include "BoolFunc.h"
#include "BitVector.h"

class BoolBit;

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
    BoolFunc getBit(std::string name);
    BitVector getBitVector(std::string name, unsigned int size);
    unsigned int numberVars() const;
private:
    std::map<KeyPair, std::shared_ptr<BoolBit>> vars;
};

#endif // BOOLMANAGER_H

