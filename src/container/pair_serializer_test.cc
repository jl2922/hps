#include "pair_serializer.h"
#include <gtest/gtest.h>
#include <utility>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(PairSerializerTest, SinglePair) {
  std::pair<std::string, int> input("aa", 3.5);
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::pair<std::string, int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::pair<std::string, int> output;
  hps::Serializer<std::pair<std::string, int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(output.first, input.first);
  EXPECT_EQ(output.second, input.second);
}
