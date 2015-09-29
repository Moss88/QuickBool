#ifndef BOOLFUNC_H
#define BOOLFUNC_H
#include "BoolBasicDefs.h"
class BoolFunc {
public:
    BoolFunc() = default;
    BoolFunc(SBoolType val);

private:
    SBoolType bValue;
};

#endif // BOOLFUNC_H

