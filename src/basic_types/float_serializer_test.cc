#include "float_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(FloatSerializerTest, TestZero) {
  const double input = 0;
  std::stringstream ss;
  hps::Serializer<double>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  double output;
  hps::Serializer<double>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestFloat) {
  const float input = 3.2;
  std::stringstream ss;
  hps::Serializer<float>::serialize(input, ss);
  EXPECT_EQ(sizeof(input), ss.str().size());
  ss.seekg(0, ss.beg);
  float output;
  hps::Serializer<float>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestDouble) {
  const double input = -4.4;
  std::stringstream ss;
  hps::Serializer<double>::serialize(input, ss);
  EXPECT_EQ(sizeof(input), ss.str().size());
  double output;
  ss.seekg(0, ss.beg);
  hps::Serializer<double>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestTwoDoubles) {
  const double input1 = 3.2;
  const double input2 = -4.4;
  std::stringstream ss;
  hps::Serializer<double>::serialize(input1, ss);
  hps::Serializer<double>::serialize(input2, ss);
  double output1;
  double output2;
  ss.seekg(0, ss.beg);
  hps::Serializer<double>::parse(output1, ss);
  hps::Serializer<double>::parse(output2, ss);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}
