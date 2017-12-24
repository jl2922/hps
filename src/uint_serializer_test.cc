#include "uint_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(UintSerializerTest, TestZero) {
  const unsigned int input = 0;
  std::stringstream ss;
  hps::Serializer<unsigned int>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestSmallUint) {
  const unsigned int input = 11;
  std::stringstream ss;
  hps::Serializer<unsigned int>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestLargeUint) {
  const unsigned int input = 3333;
  std::stringstream ss;
  hps::Serializer<unsigned int>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestTwoUints) {
  const unsigned int input1 = 22;
  const unsigned int input2 = 444;
  std::stringstream ss;
  hps::Serializer<unsigned int>::serialize(input1, ss);
  hps::Serializer<unsigned int>::serialize(input2, ss);
  ss.seekg(0, ss.beg);
  unsigned int output1;
  unsigned int output2;
  hps::Serializer<unsigned int>::parse(output1, ss);
  hps::Serializer<unsigned int>::parse(output2, ss);
  EXPECT_EQ(input1, output1);
  EXPECT_EQ(input2, output2);
}

TEST(UintSerializerTest, TestMaxUint) {
  const unsigned int input = std::numeric_limits<unsigned int>::max();
  std::stringstream ss;
  hps::Serializer<unsigned int>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ss);
  EXPECT_EQ(input, output);
}
