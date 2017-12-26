#include "float_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(FloatSerializerTest, TestZero) {
  const double input = 0;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<double, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  double output;
  hps::Serializer<double, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestFloat) {
  const float input = 3.3;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<float, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  float output;
  hps::Serializer<float, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestDouble) {
  const double input = 3.3;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<double, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  double output;
  hps::Serializer<double, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TestTwoDoubles) {
  const double input1 = 3.2;
  const double input2 = -4.4;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<double, hps::Stream>::serialize(input1, ob);
  hps::Serializer<double, hps::Stream>::serialize(input2, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  double output1;
  double output2;
  hps::Serializer<double, hps::Stream>::parse(output1, ib);
  hps::Serializer<double, hps::Stream>::parse(output2, ib);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}
