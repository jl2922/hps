#include "string_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(StringSerializerTest, TestShortString) {
  const std::string input = "test";
  std::stringstream ss;
  hps::serialize(input, ss);
  std::string output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}

TEST(StringSerializerTest, TestEmptyString) {
  const std::string input = "";
  std::stringstream ss;
  hps::serialize(input, ss);
  std::string output;
  ss.seekg(0, ss.beg);
  hps::parse(output, ss);
  EXPECT_EQ(input, output);
}
