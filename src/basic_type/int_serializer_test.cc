#include "int_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(IntSerializerTest, Zero) {
  const int input = 0;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<int, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  int output;
  hps::Serializer<int, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, SmallPositiveInt) {
  const int input = 22;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<int, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  int output;
  hps::Serializer<int, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, SmallNegativeInt) {
  const int input = -33;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<int, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  int output;
  hps::Serializer<int, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, MaxInt) {
  const int input = std::numeric_limits<int>::max();
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<int, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  int output;
  hps::Serializer<int, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, MinInt) {
  const int input = std::numeric_limits<int>::min();
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<int, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  int output;
  hps::Serializer<int, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, MaxLongLong) {
  const long long input = std::numeric_limits<long long>::max();
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<long long, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  long long output;
  hps::Serializer<long long, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, MinLongLong) {
  const long long input = std::numeric_limits<long long>::min();
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<long long, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  long long output;
  hps::Serializer<long long, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, LargeNegativeLongLong) {
  const long long input = -7363025924956902506ll;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<long long, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  long long output;
  hps::Serializer<long long, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}
