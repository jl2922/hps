#include "unordered_set_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unordered_set>
#include "../basic_types/int_serializer.h"

TEST(UnorderedSetSerializerTest, TestNoElements) {
  std::unordered_set<int> input;
  std::stringstream ss;
  hps::Serializer<std::unordered_set<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(UnorderedSetSerializerTest, TestFewElements) {
  std::unordered_set<int> input;
  input.insert(3);
  input.insert(0);
  input.insert(-133);
  std::stringstream ss;
  hps::Serializer<std::unordered_set<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::UnorderedElementsAre(3, 0, -133));
}
