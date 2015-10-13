#include "BoolAlgorithms.h"
#include "BoolExpr.h"
#include "BoolManager.h"
#include "BoolAnd.h"
#include "BoolOr.h"
#include "BoolNot.h"
#include "BoolFunc.h"

#include <iostream>
#include <string>
#include <stack>
#include <tuple>
#include <cassert>

using std::string;
using std::stack;
using std::tuple;
using std::vector;

namespace BoolAlgo {


BoolFunc generateCNF(const BoolFunc& func, string prefix, BoolManager& bMan) {
    if(!func.get()->isExpr())
        return func;
    BoolFunc CNF(true);
    unsigned int cnt = 0;
    stack<tuple<const BoolExpr*, BoolFunc>> ptrs;
    ptrs.push(std::make_tuple(dynamic_cast<const BoolExpr*>(func.get()),
                              bMan.getBit(prefix, cnt++)));
    while(!ptrs.empty())
    {
        tuple<const BoolExpr*, BoolFunc> parent = ptrs.top();
        ptrs.pop();

        const BoolExpr* expr = std::get<0>(parent);
        BoolFunc tempVar(std::get<1>(parent));
        assert(expr);

        vector<BoolFunc> operands;
        for(auto &op:*expr)
        {

            if(op->isExpr())
            {
                const BoolExpr* opExpr = dynamic_cast<const BoolExpr*>(op.get());
                BoolFunc bit = bMan.getBit(prefix, cnt++);
                ptrs.push(std::make_tuple(opExpr, bit));
                operands.push_back(bit);
            }
            else
                operands.push_back(BoolFunc(op.get()));
        }

        // Process Operands
        if(const BoolAnd* exprPtr = dynamic_cast<const BoolAnd*>(func.get()))
        {
            BoolFunc term(false);
            for(auto &op:*exprPtr)
                CNF &= !tempVar | (*op);
            for(auto &op:*exprPtr)
                term |= BoolNot(*op);
            CNF &= term | tempVar;
        }
        else if(const BoolOr* exprPtr = dynamic_cast<const BoolOr*>(func.get()))
        {
            BoolFunc term(false);
            for(auto &op:*exprPtr)
                CNF &= tempVar | BoolNot(*op);
            for(auto &op:*exprPtr)
                term |= *op;
            CNF &= term | !tempVar;
        }
        else if(const BoolNot* exprPtr = dynamic_cast<const BoolNot*>(func.get()))
        {
            assert(exprPtr->size() == 1);
            CNF &= (!std::get<1>(parent) | !operands.front()) &
                   (std::get<1>(parent) | operands.back());
        }
        else
            throw std::runtime_error("Unknown expression type for CNF generation");
    }
    return CNF;
}

bool isCNF(const BoolFunc &func) {
    if(!func.isExpr())
        return false;

    if(!func.get()->isAnd())
        return false;

    const BoolAnd* ptr = static_cast<const BoolAnd*>(func.get());
    bool noAnd = true;
    for(auto &op:*ptr)
    {
        depthTraversal(*op, [&](BoolType* element){
            if(element->isAnd())
            {
                noAnd = false;
                return false;
            }
            return true;
        });

    }
    return noAnd;
}

}

