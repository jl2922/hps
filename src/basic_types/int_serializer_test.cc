#include "int_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(IntSerializerTest, TestZero) {
  const int input = 0;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  int output;
  hps::Serializer<int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallPositiveInt) {
  const int input = 22;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  int output;
  hps::Serializer<int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallNegativeInt) {
  const int input = -33;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  int output;
  hps::Serializer<int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMaxInt) {
  const int input = std::numeric_limits<int>::max();
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  int output;
  hps::Serializer<int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMinInt) {
  const int input = std::numeric_limits<int>::min();
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  int output;
  hps::Serializer<int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMaxLongLong) {
  const long long input = std::numeric_limits<long long>::max();
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<long long>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  long long output;
  hps::Serializer<long long>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMinLongLong) {
  const long long input = std::numeric_limits<long long>::min();
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<long long>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  long long output;
  hps::Serializer<long long>::parse(output, ib);
  EXPECT_EQ(input, output);
}
