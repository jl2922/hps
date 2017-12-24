#include "uint_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(UintSerializerTest, TestZero) {
  const unsigned int input = 0;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestSmallUint) {
  const unsigned int input = 27;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestLargeUint) {
  const unsigned int input = 300;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestTwoUints) {
  const unsigned int input1 = 27;
  const unsigned int input2 = 300;
  std::stringstream ss;
  hps::serialize(input1, ss);
  hps::serialize(input2, ss);
  unsigned int output1;
  unsigned int output2;
  ss.seekg(0, ss.beg);
  hps::parse(output1, ss);
  hps::parse(output2, ss);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}

TEST(UintSerializerTest, TestMaxUint) {
  const unsigned int input = std::numeric_limits<unsigned int>::max();
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

// Manual Test:
// Expect compilation errors for unsupported types.
