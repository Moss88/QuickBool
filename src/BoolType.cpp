#include "BoolType.h"
namespace QuickBool {
std::ostream& operator<< (std::ostream& outStream, const BoolType& val) {
    outStream << val.toString();
    return outStream;
}
}
