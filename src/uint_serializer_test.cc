#include "uint_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(UintSerializerTest, TestZero) {
  const unsigned int input = 0;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestSmallUint) {
  const unsigned int input = 27;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestLargeUint) {
  const unsigned int input = 300;
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestMaxUint) {
  const unsigned int input = std::numeric_limits<unsigned int>::max();
  std::stringstream ss;
  hps::serialize(input, ss);
  unsigned int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

// Manual Test:
// Expect compilation errors for unsupported types.
