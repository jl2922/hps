#include "int_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(IntSerializerTest, TestZero) {
  const int input = 0;
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallPositiveInt) {
  const int input = 27;
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallNegativeInt) {
  const int input = -27;
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestLargePositiveInt) {
  const int input = 300;
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestLargeNegativeInt) {
  const int input = -300;
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMaxInt) {
  const int input = std::numeric_limits<int>::max();
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMinInt) {
  const int input = std::numeric_limits<int>::min();
  std::stringstream ss;
  hps::serialize(input, ss);
  int output;
  hps::parse(&output, ss);
  EXPECT_EQ(input, output);
}

// Manual Test:
// Expect compilation errors for unsupported types.
