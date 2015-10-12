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

    BoolFunc eq = a & b;
    EXPECT_TRUE(BoolAlgo::isCNF(eq));
    eq |= c;
    EXPECT_FALSE(BoolAlgo::isCNF(eq));
    eq = (a | b) & (!a | c);
    EXPECT_TRUE(BoolAlgo::isCNF(eq));
    eq = (a | b) & (!a | c) & !d;
    EXPECT_TRUE(BoolAlgo::isCNF(eq));
}

TEST(BoolAlgo, CNF) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc c = bm.getBit("c");

    BoolFunc eq = a | (b & c);
    BoolFunc cnf = BoolAlgo::generateCNF(eq, "tmp", bm);
    EXPECT_TRUE(BoolAlgo::isCNF(cnf));
}

