#include "int_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(IntSerializerTest, TestZero) {
  const int input = 0;
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallPositiveInt) {
  const int input = 22;
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestSmallNegativeInt) {
  const int input = -33;
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestLargePositiveInt) {
  const int input = 3333;
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestLargeNegativeInt) {
  const int input = -4444;
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMaxInt) {
  const int input = std::numeric_limits<int>::max();
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMinInt) {
  const int input = std::numeric_limits<int>::min();
  std::stringstream ss;
  hps::Serializer<int>::serialize(input, ss);
  int output;
  ss.seekg(0, ss.beg);
  hps::Serializer<int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMaxLongLong) {
  const long long input = std::numeric_limits<long long>::max();
  std::stringstream ss;
  hps::Serializer<long long>::serialize(input, ss);
  long long output;
  ss.seekg(0, ss.beg);
  hps::Serializer<long long>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(IntSerializerTest, TestMinLongLong) {
  const long long input = std::numeric_limits<long long>::min();
  std::stringstream ss;
  hps::Serializer<long long>::serialize(input, ss);
  long long output;
  ss.seekg(0, ss.beg);
  hps::Serializer<long long>::parse(output, ss);
  EXPECT_EQ(input, output);
}
