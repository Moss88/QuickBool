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
#include <unistd.h>

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
        if(func.get()->isAnd())
        {
            BoolFunc term(false);
            for(auto &op:operands)
                CNF &= !tempVar | op;
            for(auto &op:operands)
                term |= !op;
            CNF &= term | tempVar;
        }
        else if(func.get()->isOr())
        {
            BoolFunc term(false);
            for(auto &op:operands)
                CNF &= tempVar | !BoolFunc(op.get());

            for(auto &op:operands)
                term |= op;
            CNF &= term | !tempVar;
        }
        else if(func.get()->isNot())
        {
            assert(operands.size() == 1);
            CNF &= (!tempVar | !operands.front()) &
                   (tempVar | operands.front());
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
        if((literal->isNot() && !isCNFNotTerm(static_cast<const BoolNot*>(literal.get()))) ||
          (!literal->isNot() && !literal->isVar()))
            return false;
    }
    return true;
}

bool isCNF(const BoolFunc &func) {
    if(!func.isExpr())
        return false;
    if(func.get()->isOr())
       return isCNFOrTerm(static_cast<const BoolOr*>(func.get()));
    else if(!func.get()->isAnd())
       return false;

    const BoolAnd* ptr = static_cast<const BoolAnd*>(func.get());
    for(auto &op:*ptr)
    {
        if(op->isOr() && !isCNFOrTerm(static_cast<const BoolOr*>(op.get())))
            return false;
        else if(op->isNot() && !isCNFNotTerm(static_cast<const BoolNot*>(op.get())))
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


bool runLingelingSat(std::string &&dimacsStr) {
    int p2cFD[2];
    int c2pFD[2];

    if(pipe(p2cFD) == -1)
        std::perror("BoolAlgorithms.runLinglingSat: Failed to generate p2cFD pipe");

    if(pipe(c2pFD) == -1)
        std::perror("BoolAlgorithms.runLinglingSat: Failed to generate c2pFD pipe");

    FILE *fp = popen("which lingeling", "r");

    char path[256];
    if(fgets(path, 256, fp) == nullptr)
        throw std::runtime_error("BoolAlgorithms: Failed to get pipe path");
    pclose(fp);
    string filePath = path;


    // Fork
    if(!fork())
    {
        dup2(c2pFD[1], 1);
        close(c2pFD[0]);
        close(c2pFD[1]);
        dup2(p2cFD[0], 0);
        close(p2cFD[0]);
        close(p2cFD[1]);

        int error = execl((filePath.substr(0,filePath.length() - 1)).c_str(), (filePath.substr(0,filePath.length() - 1)).c_str(), NULL);
        if(error == -1)
            throw std::runtime_error("isSat process error " + std::to_string(error));
    }
    else
    {
        char buffer[256];
        close(p2cFD[0]);
        close(c2pFD[1]);
        if(write(p2cFD[1], dimacsStr.c_str(), dimacsStr.length()) == -1)
            std::perror("BoolAlgorithms.runLinglingSat: Failed to write to pipe");

        close(p2cFD[1]);
        FILE *in = fdopen(c2pFD[0], "r");
        while (fgets(buffer, 256, in))
        {
            if(buffer[0] == 's')
            {
                string str(buffer);
                size_t idx = str.find("UNSATISFIABLE");
                if(idx == string::npos)
                    return true;
                else
                    return false;
            }
        }
        close(c2pFD[0]);
    }
    return true;
}


bool isSat(const BoolFunc& func) {
    // Get Unique Ids for all bits
    unsigned int idCnt = 1;
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
    unsigned int nClauses = 0;
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
                buffer << bitId[bit] << " ";

            }
            else if(op->isVar())
            {
                const BoolBit* bit = static_cast<const BoolBit*>(op.get());
                buffer << bitId[bit] << " ";
            }
        }
        buffer << "0" << std::endl;
        ++nClauses;
    }


    bool satResult = runLingelingSat("p cnf " + std::to_string(bitId.size()) + " " +
                                     std::to_string(nClauses) + "\n" + buffer.str());

    std::string dimacFile = "p cnf " + std::to_string(bitId.size()) + " " +
                            std::to_string(nClauses) + "\n" + buffer.str();
    std::cout << dimacFile << std::endl;

    return satResult;
}


}

