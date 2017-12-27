#include "map_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <map>
#include "../basic_type/basic_type.h"

TEST(MapSerializerTest, NoElements) {
  std::map<std::string, int> input;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::map<std::string, int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::map<std::string, int> output;
  hps::Serializer<std::map<std::string, int>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(MapSerializerTest, FewElements) {
  std::map<std::string, int> input;
  input["aa"] = 33;
  input["bb"] = 0;
  input["cc"] = -333;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::map<std::string, int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::map<std::string, int> output;
  hps::Serializer<std::map<std::string, int>, hps::Stream>::parse(output, ib);
  EXPECT_EQ(output.size(), input.size());
  EXPECT_THAT(output, testing::Contains(testing::Key("aa")));
  EXPECT_THAT(output, testing::Contains(testing::Key("bb")));
  EXPECT_THAT(output, testing::Contains(testing::Key("cc")));
  EXPECT_EQ(input.at("aa"), output.at("aa"));
  EXPECT_EQ(input.at("bb"), output.at("bb"));
  EXPECT_EQ(input.at("cc"), output.at("cc"));
}
