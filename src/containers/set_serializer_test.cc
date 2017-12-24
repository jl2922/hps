#include "set_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <set>
#include "../basic_types/int_serializer.h"

TEST(SetSerializerTest, TestNoElements) {
  std::set<int> input;
  std::stringstream ss;
  hps::Serializer<std::set<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::set<int> output;
  hps::Serializer<std::set<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(SetSerializerTest, TestFewElements) {
  std::set<int> input;
  input.insert(3);
  input.insert(0);
  input.insert(-133);
  std::stringstream ss;
  hps::Serializer<std::set<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::set<int> output;
  hps::Serializer<std::set<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::UnorderedElementsAre(3, 0, -133));
}
