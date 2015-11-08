#ifndef BOOLBASICDEFS_H
#define BOOLBASICDEFS_H
#include<string>
#include<memory>
namespace QuickBool {
class BoolType;
class BoolBit;

typedef std::shared_ptr<BoolType> SBoolType;
typedef std::unique_ptr<BoolType> UBoolType;
typedef std::shared_ptr<BoolBit> SBoolBit;
typedef std::unique_ptr<BoolBit> UBoolBit;

enum class BoolValue {Unknown, One, Zero, DontCare};

std::string to_string(const BoolValue& value);
}
#endif // BOOLBASICDEFS_H

