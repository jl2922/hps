#include "string_serializer.h"
#include "../buffer/buffer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(StringSerializerTest, ShortString) {
  const std::string input = "test";
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::string, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::string output;
  hps::Serializer<std::string, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(StringSerializerTest, EmptyString) {
  const std::string input = "";
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::string, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::string output;
  hps::Serializer<std::string, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
}
