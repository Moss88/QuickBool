#ifndef BOOLALGORITHMS_H
#define BOOLALGORITHMS_H
#include "BoolFunc.h"
#include "BoolExpr.h"
#include <functional>

namespace QuickBool {
class BoolManager;
namespace BoolAlgo {


template<typename BFunc, typename Func>
bool depthRecur(BFunc* expr, Func func) {
    if(expr == nullptr)
        return false;
    if(expr->isExpr())
    {
        auto expression = dynamic_cast<const BoolExpr*>(expr);
        for(auto &operand:*expression)
        {
            bool result = depthRecur(operand.get(), func);
            if(!result)
                return false;
        }
    }
    return func(expr);
}

template<typename BFunc, typename Func>
void depthTraversal(BFunc& expr, Func func) {
    if(expr.get() != nullptr)
        depthRecur(expr.get(), func);
}

template<typename Func>
void depthTraversal(BoolType& expr, Func func) {
    depthRecur(&expr, func);
}

BoolFunc generateCNF(const BoolFunc& func, std::string prefix, BoolManager& bMan);
bool isCNF(const BoolFunc &func);
std::vector<BoolFunc> isSat(const BoolFunc& func);



}
}
#endif // BOOLALGORITHMS_H

