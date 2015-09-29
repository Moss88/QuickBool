#include "gtest/gtest.h"
#include<iostream>
using namespace std;
TEST(BoolBit, Test) {
    cout << "Hello World" << endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
