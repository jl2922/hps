#include "float_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(FloatSerializerTest, TestZero) {
  const double input = 0;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<double>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  double output;
  hps::Serializer<double>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestFloat) {
  const float input = 3.3;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<float>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  float output;
  hps::Serializer<float>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestDouble) {
  const double input = 3.3;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<double>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  double output;
  hps::Serializer<double>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestTwoDoubles) {
  const double input1 = 3.2;
  const double input2 = -4.4;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<double>::serialize(input1, ob);
  hps::Serializer<double>::serialize(input2, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  double output1;
  double output2;
  hps::Serializer<double>::parse(output1, ib);
  hps::Serializer<double>::parse(output2, ib);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}
