#include "BoolAlgorithms.h"
#include "BoolExpr.h"
/*
namespace BoolAlgo {

bool depthRecur(const BoolType* expr, std::function<bool(const BoolType*)> func) {
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


void depthTraversal(const BoolFunc& expr, std::function<bool(const BoolType*)> func) {
    if(expr.get() != nullptr)
        depthRecur(expr.get(), func);
}


}
*/
