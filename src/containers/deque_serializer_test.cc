#include "deque_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <deque>
#include "../basic_types/int_serializer.h"

TEST(DequeSerializerTest, TestNoElements) {
  std::deque<int> input;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::deque<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(DequeSerializerTest, TestFewElements) {
  std::deque<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::deque<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}
