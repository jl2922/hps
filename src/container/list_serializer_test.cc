#include "list_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <list>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(ListSerializerTest, NoElements) {
  std::list<int> input;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::list<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::list<int> output;
  hps::Serializer<std::list<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(ListSerializerTest, FewElements) {
  std::list<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::list<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::list<int> output;
  hps::Serializer<std::list<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}
