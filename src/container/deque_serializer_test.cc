#include "deque_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <deque>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(DequeSerializerTest, NoElements) {
  std::deque<int> input;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::deque<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(DequeSerializerTest, FewElements) {
  std::deque<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::deque<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::deque<int> output;
  hps::Serializer<std::deque<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}
