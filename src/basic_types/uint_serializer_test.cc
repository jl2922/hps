#include "uint_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(UintSerializerTest, TestZero) {
  const unsigned int input = 0;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<unsigned int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestSmallUint) {
  const unsigned int input = 22;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<unsigned int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestLargeUint) {
  const unsigned int input = 3333;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<unsigned int>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, TestFewUints) {
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  const size_t N = 10;
  for (size_t i = 0; i < N; i++) {
    hps::Serializer<unsigned int>::serialize(i, ob);
  }
  ob.flush();

  hps::InputBuffer ib(ss);
  for (size_t i = 0; i < N; i++) {
    unsigned int output;
    hps::Serializer<unsigned int>::parse(output, ib);
    EXPECT_EQ(i, output);
  }
}

TEST(UintSerializerTest, TestMaxUint) {
  const unsigned long long input = std::numeric_limits<unsigned long long>::max();
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<unsigned long long>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  unsigned long long output;
  hps::Serializer<unsigned long long>::parse(output, ib);
  EXPECT_EQ(input, output);
}
