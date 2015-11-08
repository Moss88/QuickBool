#include "gtest/gtest.h"
#include "BoolManager.h"
#include "BoolBit.h"
#include<iostream>
using namespace std;
using namespace QuickBool;
TEST(BoolManager, GetVar) {
    BoolManager bm;
    BoolFunc a = bm.getBit("a");
    BoolFunc b = bm.getBit("b");
    BoolFunc aCopy = bm.getBit("a");

    BoolBit *aPtr = dynamic_cast<BoolBit*>(a.get());
    BoolBit *bPtr = dynamic_cast<BoolBit*>(b.get());
    BoolBit *aCopyPtr = dynamic_cast<BoolBit*>(aCopy.get());
    ASSERT_TRUE(aPtr);
    ASSERT_TRUE(bPtr);
    ASSERT_TRUE(aCopyPtr);

    EXPECT_EQ(aPtr->getName(), aCopyPtr->getName());
    EXPECT_EQ(aPtr->getIndex(), aCopyPtr->getIndex());
    EXPECT_NE(bPtr->getName(), aPtr->getName());
    bm.setValue(BoolValue::One, "a");
    EXPECT_EQ(aPtr->value(), BoolValue::One);
    EXPECT_EQ(aCopyPtr->value(), BoolValue::One);
}

TEST(BoolManager, GetVector)
{
    BoolManager bm;
    BitVector bv = bm.getBitVector("a", 2);
    ASSERT_EQ(bv.size(), 2);
    EXPECT_EQ(bv.begin()->toString(), "a[0]");
    EXPECT_EQ((bv.begin() + 1)->toString(), "a[1]");
}
