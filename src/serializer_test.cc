#include "serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(SerializerTest, TestParseAndReturnInt) {
  const int input = 33;
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  const int output = hps::parse<int>(ss);
  EXPECT_EQ(input, output);
}

TEST(SerializerTest, TestParseAndReturnVector) {
  const std::vector<int> input({3, -5, 222});
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  const std::vector<int> output = hps::parse<std::vector<int>>(ss);
  EXPECT_THAT(output, testing::ElementsAre(3, -5, 222));
}