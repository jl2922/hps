#include "list_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <list>
#include "../basic_types/int_serializer.h"

TEST(ListSerializerTest, TestNoElements) {
  std::list<int> input;
  std::stringstream ss;
  hps::Serializer<std::list<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::list<int> output;
  hps::Serializer<std::list<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(ListSerializerTest, TestFewElements) {
  std::list<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::Serializer<std::list<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::list<int> output;
  hps::Serializer<std::list<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}
