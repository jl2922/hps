#include "float_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>
#include "../buffer/buffer.h"

TEST(FloatSerializerTest, Zero) {
  const double input = 0;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<double, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  double output;
  hps::Serializer<double, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, Float) {
  const float input = 3.3;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<float, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  float output;
  hps::Serializer<float, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, Double) {
  const double input = 3.3;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<double, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  double output;
  hps::Serializer<double, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(FloatSerializerTest, TwoDoubles) {
  const double input1 = 3.2;
  const double input2 = -4.4;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<double, hps::StreamOutputBuffer>::serialize(input1, ob);
  hps::Serializer<double, hps::StreamOutputBuffer>::serialize(input2, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  double output1;
  double output2;
  hps::Serializer<double, hps::StreamInputBuffer>::parse(output1, ib);
  hps::Serializer<double, hps::StreamInputBuffer>::parse(output2, ib);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}
