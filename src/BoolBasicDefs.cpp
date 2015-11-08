#include "BoolBasicDefs.h"
namespace QuickBool {
std::string to_string(const BoolValue& value) {
    if(value == BoolValue::One)
        return "1";
    else if(value == BoolValue::Zero)
        return "0";
    else
        return "???";
}
}
