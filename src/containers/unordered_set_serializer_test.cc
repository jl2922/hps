#include "unordered_set_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unordered_set>
#include "../basic_types/int_serializer.h"

TEST(UnorderedSetSerializerTest, TestNoElements) {
  std::unordered_set<int> input;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::unordered_set<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(UnorderedSetSerializerTest, TestFewElements) {
  std::unordered_set<int> input;
  input.insert(3);
  input.insert(0);
  input.insert(-133);
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::unordered_set<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::UnorderedElementsAre(3, 0, -133));
}
