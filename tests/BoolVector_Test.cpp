#include "gtest/gtest.h"
#include "BoolManager.h"
#include "BitVector.h"
#include "BoolExpr.h"
#include "BoolAlgorithms.h"

#include<iostream>
using namespace std;
using namespace QuickBool;
TEST(BoolVector, lt) {
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc lt = vA < vB;
    bm.setValue(BoolValue::One, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::One, "b", 1);
    BoolValue val = lt.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::One, "a", 1);
    val = lt.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::Zero, "a", 0);
    val = lt.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);
}

TEST(BoolVector, eq)
{
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc eq = vA == vB;
    bm.setValue(BoolValue::Zero, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::Zero, "b", 1);

    BoolValue val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::One, "a", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::One, "b", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::One);
}


TEST(BoolVector, lte) {
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc lte = vA <= vB;
    bm.setValue(BoolValue::One, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::One, "b", 1);

    BoolValue val = lte.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::One, "a", 1);
    val = lte.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::Zero, "a", 0);
    val = lte.evaluate();
    EXPECT_EQ(val, BoolValue::One);
}

TEST(BoolVector, ne) {
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc eq = vA != vB;
    bm.setValue(BoolValue::Zero, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::Zero, "b", 1);

    BoolValue val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::One, "a", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::One, "b", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);
}

TEST(BoolVector, gte) {
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc gte = vA >= vB;
    bm.setValue(BoolValue::One, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::One, "b", 1);

    BoolValue val = gte.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::One, "a", 1);
    val = gte.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::Zero, "a", 0);
    val = gte.evaluate();
    EXPECT_EQ(val, BoolValue::One);
}

TEST(BoolVector, gt) {
    BoolManager bm;
    BitVector vA = bm.getBitVector("a", 2);
    BitVector vB = bm.getBitVector("b", 2);


    BoolFunc gt = vA > vB;
    bm.setValue(BoolValue::One, "a", 0);
    bm.setValue(BoolValue::Zero, "a", 1);
    bm.setValue(BoolValue::Zero, "b", 0);
    bm.setValue(BoolValue::One, "b", 1);
    BoolValue val = gt.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);

    bm.setValue(BoolValue::One, "a", 1);
    val = gt.evaluate();
    EXPECT_EQ(val, BoolValue::One);

    bm.setValue(BoolValue::Zero, "a", 0);
    val = gt.evaluate();
    EXPECT_EQ(val, BoolValue::Zero);
}
