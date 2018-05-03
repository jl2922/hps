#include "uint_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>
#include "../buffer/buffer.h"

TEST(UintSerializerTest, Zero) {
  const unsigned int input = 0;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<unsigned int, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, SmallUint) {
  const unsigned int input = 22;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<unsigned int, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, LargeUint) {
  const unsigned int input = 3333;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<unsigned int, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  unsigned int output;
  hps::Serializer<unsigned int, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(UintSerializerTest, FewUints) {
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  const size_t N = 10;
  for (size_t i = 0; i < N; i++) {
    hps::Serializer<unsigned int, hps::StreamOutputBuffer>::serialize(i, ob);
  }
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  for (size_t i = 0; i < N; i++) {
    unsigned int output;
    hps::Serializer<unsigned int, hps::StreamInputBuffer>::parse(output, ib);
    EXPECT_EQ(i, output);
  }
}

TEST(UintSerializerTest, MaxUint) {
  const unsigned long long input = std::numeric_limits<unsigned long long>::max();
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<unsigned long long, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  unsigned long long output;
  hps::Serializer<unsigned long long, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}
