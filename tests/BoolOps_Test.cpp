#include "gtest/gtest.h"
#include "BoolManager.h"
#include "BitVector.h"
#include "BoolExpr.h"
#include "BoolAlgorithms.h"

#include<iostream>
using namespace std;

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

TEST(BoolOp, And) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");
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
}


