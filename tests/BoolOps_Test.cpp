#include "gtest/gtest.h"
#include "BoolManager.h"
#include "BitVector.h"
#include "BoolExpr.h"
#include "BoolAlgorithms.h"
#include "BoolAnd.h"

#include<iostream>
#include<functional>

using namespace std;
using namespace QuickBool;

unsigned int treeDepth(const BoolType* func, unsigned int cnt = 0) {
    if(func->isExpr())
    {
        auto maxDepth = cnt;
        const BoolExpr* expr = static_cast<const BoolExpr*>(func);
        for(auto &op:*expr)
        {
            unsigned int newDepth = treeDepth(op.get(), cnt);
            if(newDepth > maxDepth)
                maxDepth = newDepth;
        }
        cnt = maxDepth;
    }
    return ++cnt;
}

unsigned int litCount(const BoolType* func) {
    unsigned int varCount = 0;
    if(func->isExpr())
    {
        const BoolExpr* expr = static_cast<const BoolExpr*>(func);
        for(auto &op:*expr)
            varCount += litCount(op.get());
    }
    else if(func->isVar() | func->isOne() | func->isZero())
        varCount++;
    return varCount;
}


TEST(BoolOp, Not) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    bm.setValue(BoolValue::Zero, "a");
    EXPECT_EQ(a.evaluate(), BoolValue::Zero);
    BoolFunc aNot = !a;
    EXPECT_EQ(aNot.evaluate(), BoolValue::One);
    BoolFunc aNotNot = !aNot;
    EXPECT_EQ(aNotNot.evaluate(), BoolValue::Zero);
}

TEST(BoolOp, AndNoValue) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");
    BoolFunc d = bm.getBit("d");

    BoolFunc func = a & b;
    func &= c & d;
    auto exprPtr = dynamic_cast<BoolAnd*>(func.get());
    ASSERT_TRUE(exprPtr);
    EXPECT_EQ(exprPtr->size(), 4);
}

TEST(BoolOp, And) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");
    BoolFunc d = bm.getBit("d");
    bm.setValue(BoolValue::One, "a");
    bm.setValue(BoolValue::One, "b");
    bm.setValue(BoolValue::Zero, "c");

    BoolFunc func = a & b;
    EXPECT_EQ(func.evaluate(), BoolValue::One);
    func &= c;
    EXPECT_EQ(func.evaluate(), BoolValue::Zero);
    bm.setValue(BoolValue::One, "c");
    EXPECT_EQ(func.evaluate(), BoolValue::One);
}

TEST(BoolOp, Or) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");
    bm.setValue(BoolValue::Zero, "a");
    bm.setValue(BoolValue::Zero, "b");
    bm.setValue(BoolValue::One, "c");

    BoolFunc func = a | b;
    EXPECT_EQ(func.evaluate(), BoolValue::Zero);
    func |= c;
    EXPECT_EQ(func.evaluate(), BoolValue::One);
    bm.setValue(BoolValue::Zero, "c");
    EXPECT_EQ(func.evaluate(), BoolValue::Zero);

    func = a | b | c;
    EXPECT_EQ(treeDepth(func.get()), 2);
}

TEST(BoolOp, Constants)
{
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");

    BoolFunc one(true), zero(false);
    BoolFunc eq = a & one;
    EXPECT_EQ(treeDepth(eq.get()), 1);
    eq = a & b & one;
    EXPECT_EQ(treeDepth(eq.get()), 2);
    EXPECT_EQ(litCount(eq.get()), 2);

    eq = a & zero;
    EXPECT_TRUE(eq.get()->isZero());

    BoolFunc oneCpy = one;
    oneCpy &= a;
    EXPECT_EQ(litCount(oneCpy.get()), 1);
    EXPECT_TRUE(oneCpy.get()->isVar());

    eq = a | zero;
    EXPECT_EQ(treeDepth(eq.get()), 1);
    eq = a | b | zero;
    EXPECT_EQ(treeDepth(eq.get()), 2);
    EXPECT_EQ(litCount(eq.get()), 2);

    eq = a | one;
    EXPECT_TRUE(eq.get()->isOne());

}


