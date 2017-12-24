#include "unordered_map_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unordered_map>
#include "../basic_types/int_serializer.h"
#include "../basic_types/string_serializer.h"

TEST(UnorderedmapSerializerTest, TestNoElements) {
  std::unordered_map<std::string, int> input;
  std::stringstream ss;
  hps::Serializer<std::unordered_map<std::string, int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::unordered_map<std::string, int> output;
  hps::Serializer<std::unordered_map<std::string, int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(UnorderedmapSerializerTest, TestFewElements) {
  std::unordered_map<std::string, int> input;
  input["aa"] = 33;
  input["bb"] = 0;
  input["cc"] = -333;
  std::stringstream ss;
  hps::Serializer<std::unordered_map<std::string, int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::unordered_map<std::string, int> output;
  hps::Serializer<std::unordered_map<std::string, int>>::parse(output, ss);
  EXPECT_EQ(output.size(), input.size());
  EXPECT_THAT(output, testing::Contains(testing::Key("aa")));
  EXPECT_THAT(output, testing::Contains(testing::Key("bb")));
  EXPECT_THAT(output, testing::Contains(testing::Key("cc")));
  EXPECT_EQ(input.at("aa"), output.at("aa"));
  EXPECT_EQ(input.at("bb"), output.at("bb"));
  EXPECT_EQ(input.at("cc"), output.at("cc"));
}
