#include "string_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(StringSerializerTest, TestShortString) {
  const std::string input = "test";
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::string>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::string output;
  hps::Serializer<std::string>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(StringSerializerTest, TestEmptyString) {
  const std::string input = "";
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::string>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::string output;
  hps::Serializer<std::string>::parse(output, ib);
  EXPECT_EQ(input, output);
}
