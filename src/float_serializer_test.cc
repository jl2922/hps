#include "float_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(FloatSerializerTest, TestZero) {
  const double input = 0;
  std::stringstream ss;
  hps::serialize(input, ss);
  double output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestFloat) {
  const float input = 3.2;
  std::stringstream ss;
  hps::serialize(input, ss);
  EXPECT_EQ(sizeof(input), ss.str().size());
  float output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestDouble) {
  const double input = -4.4;
  std::stringstream ss;
  hps::serialize(input, ss);
  EXPECT_EQ(sizeof(input), ss.str().size());
  double output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestTwoDoubles) {
  const double input1 = 3.2;
  const double input2 = -4.4;
  std::stringstream ss;
  hps::serialize(input1, ss);
  hps::serialize(input2, ss);
  double output1;
  double output2;
  ss.seekg(0, ss.beg);
  hps::parse(output1, ss);
  hps::parse(output2, ss);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}

// Manual Test:
// Expect compilation errors for unsupported types.
