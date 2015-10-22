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
#include <map>
#include <sstream>
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

bool isCNFNotTerm(const BoolNot* expr) {
    return expr->begin()->get()->isVar();
}

bool isCNFOrTerm(const BoolOr* expr) {
    for(auto &literal:*expr)
    {
        if(literal->isNot() &&
           !isCNFNotTerm(static_cast<const BoolNot*>(literal.get())))
            return false;
        else if(!literal->isVar())
            return false;
    }
    return true;
}

bool isCNF(const BoolFunc &func) {
    if(!func.isExpr())
        return false;
    else if(func.get()->isOr())
       return isCNFOrTerm(static_cast<const BoolOr*>(func.get()));


    const BoolAnd* ptr = static_cast<const BoolAnd*>(func.get());
    for(auto &op:*ptr)
    {
        if(op->isOr() && !isCNFOrTerm(static_cast<const BoolOr*>(op.get())))
            return false;
    }
    return true;
}

struct BoolBitCmp{
    bool operator()(const BoolBit* a, const BoolBit *b)
    {
        int cmpResult = a->getName().compare(b->getName());
        return (cmpResult < 0) ||
               ((cmpResult == 0) && (a->getIndex() < b->getIndex()));
    }
};

std::vector<BoolValue> isSat(const BoolFunc& func) {
    // Get Unique Ids for all bits
    std::cout << "Processing " << func << std::endl;
    unsigned int idCnt = 0;
    std::map<const BoolBit*, unsigned int, BoolBitCmp> bitId;
    auto addBits = [&](const BoolType *operand){
        if(operand->isVar())
        {
            auto rIter = bitId.find(static_cast<const BoolBit*>(operand));
            if(rIter == bitId.end())
                bitId[static_cast<const BoolBit*>(operand)] = idCnt++;
        }
        return true;
    };
    depthTraversal(func, addBits);
    const BoolAnd* andExpr = dynamic_cast<const BoolAnd*>(func.get());
    if(!andExpr)
        throw std::runtime_error("IsSat: function is not CNF, expression not and");
    std::stringstream buffer;
    for(auto &term:*andExpr)
    {
        const BoolOr* orExpr = dynamic_cast<const BoolOr*>(term.get());
        if(!orExpr)
            throw std::runtime_error("IsSat: function is not CNF, expression not or");
        for(auto &op:*orExpr)
        {
            if(op->isExpr())
            {
                const BoolNot* notOp = dynamic_cast<const BoolNot*>(op.get());
                const BoolBit* bit = dynamic_cast<const BoolBit*>(notOp->begin()->get());
                std::cout << "Got here" << std::endl;
                buffer << bitId[bit] << " ";
                std::cout << "Made it past" << std::endl;

            }
            else if(op->isVar())
            {
                std::cout << "Got here" << std::endl;
                if(!op)
                    throw std::runtime_error("Error nullptr for operand type");
                if(!op.get())
                    throw std::runtime_error("Error nullptr for operand type");
                const BoolBit* bit = dynamic_cast<const BoolBit*>(op.get());
                std::cout << "past dynamic cast" << std::endl;

                if(!bit)
                    throw std::runtime_error("Error nullptr for bit type");
                buffer << bitId[bit] << " ";
                std::cout << "Made it past" << std::endl;
            }
        }
        buffer << std::endl;
    }
    std::cout << buffer.str() << std::endl;
    return std::vector<BoolValue>();
}


}

