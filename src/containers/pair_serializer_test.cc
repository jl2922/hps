#include "pair_serializer.h"
#include <gtest/gtest.h>
#include <utility>
#include "../basic_types/int_serializer.h"
#include "../basic_types/string_serializer.h"

TEST(PairSerializerTest, TestNormalPair) {
  std::pair<std::string, int> input("aa", 3.5);
  std::stringstream ss;
  hps::Serializer<std::pair<std::string, int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::pair<std::string, int> output;
  hps::Serializer<std::pair<std::string, int>>::parse(output, ss);
  EXPECT_EQ(output.first, input.first);
  EXPECT_EQ(output.second, input.second);
}
