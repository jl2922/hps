#include "string_serializer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

TEST(StringSerializerTest, ShortString) {
  const std::string input = "test";
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::string, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::string output;
  hps::Serializer<std::string, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}

TEST(StringSerializerTest, EmptyString) {
  const std::string input = "";
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::string, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::string output;
  hps::Serializer<std::string, hps::Stream>::parse(output, ib);
  EXPECT_EQ(input, output);
}
