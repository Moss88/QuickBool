#include "gtest/gtest.h"
#include "BoolManager.h"
#include "BoolBit.h"
#include "BoolAlgorithms.h"
#include<iostream>
using namespace std;
TEST(BoolAlgo, isCNF) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");
    BoolFunc d = bm.getBit("c");

    BoolFunc eq = (a | b);
    EXPECT_TRUE(BoolAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = a | (c & b);
    EXPECT_FALSE(BoolAlgo::isCNF(eq)) << "Failed CNF: "
                                      << eq;
    eq = (a | b) & (!a | c);
    EXPECT_TRUE(BoolAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = (a | b) & (!a | c) & !d;
    EXPECT_TRUE(BoolAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = (a | b) & !(a | c);
    EXPECT_FALSE(BoolAlgo::isCNF(eq)) << "Failed CNF: "
                                      << eq;
}

TEST(BoolAlgo, CNF) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");

    BoolFunc eq = a & b & c;
    BoolFunc cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    ASSERT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    bm.setValue(BoolValue::One, "a");
    bm.setValue(BoolValue::One, "b");
    bm.setValue(BoolValue::One, "c");
    bm.setValue(BoolValue::One, "tmp");
    EXPECT_EQ(cnf.evaluate(), BoolValue::One);
    bm.setValue(BoolValue::Zero, "c");
    EXPECT_EQ(cnf.evaluate(), BoolValue::Zero);
    bm.setValue(BoolValue::Zero, "tmp");
    EXPECT_EQ(cnf.evaluate(), BoolValue::One);

    eq = a | b | c;
    cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    EXPECT_TRUE(BoolAlgo::isCNF(cnf));
    bm.setValue(BoolValue::Zero, "a");
    bm.setValue(BoolValue::Zero, "b");
    bm.setValue(BoolValue::Zero, "c");
    bm.setValue(BoolValue::Zero, "tmp");
    EXPECT_EQ(cnf.evaluate(), BoolValue::One);
    bm.setValue(BoolValue::One, "c");
    EXPECT_EQ(cnf.evaluate(), BoolValue::Zero);
    bm.setValue(BoolValue::One, "tmp");
    EXPECT_EQ(cnf.evaluate(), BoolValue::One);

    eq = (a | b) & !c;
    cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    EXPECT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;

    eq = a & (b | c);
    cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    EXPECT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
}


TEST(BoolAlgo, isSat) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");

    BoolFunc eq = a & (b | c);
    BoolFunc cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    ASSERT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_TRUE(BoolAlgo::isSat(cnf).size());


    eq = a & !a;
    cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    ASSERT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_FALSE(BoolAlgo::isSat(cnf).size());

    eq = a | b | !a;
    cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    ASSERT_TRUE(BoolAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_TRUE(BoolAlgo::isSat(cnf).size());

}

