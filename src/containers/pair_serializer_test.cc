#include "pair_serializer.h"
#include <gtest/gtest.h>
#include <utility>
#include "../basic_types/int_serializer.h"
#include "../basic_types/string_serializer.h"

TEST(PairSerializerTest, SinglePair) {
  std::pair<std::string, int> input("aa", 3.5);
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::pair<std::string, int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::pair<std::string, int> output;
  hps::Serializer<std::pair<std::string, int>, hps::Stream>::parse(output, ib);
  EXPECT_EQ(output.first, input.first);
  EXPECT_EQ(output.second, input.second);
}
