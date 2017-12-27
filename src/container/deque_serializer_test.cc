#include "deque_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <deque>
#include "../basic_type/basic_type.h"

TEST(DequeSerializerTest, NoElements) {
  std::deque<int> input;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::deque<int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(DequeSerializerTest, FewElements) {
  std::deque<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::deque<int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}
