#ifndef BOOLBASICDEFS_H
#define BOOLBASICDEFS_H

#include<memory>
class BoolType;

typedef std::shared_ptr<BoolType> SBoolType;
enum class BoolValue {Unknown, One, Zero};


#endif // BOOLBASICDEFS_H

