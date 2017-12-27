#include "unordered_set_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unordered_set>
#include "../basic_type/basic_type.h"

TEST(UnorderedSetSerializerTest, NoElements) {
  std::unordered_set<int> input;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::unordered_set<int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(UnorderedSetSerializerTest, FewElements) {
  std::unordered_set<int> input;
  input.insert(3);
  input.insert(0);
  input.insert(-133);
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::unordered_set<int>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::unordered_set<int> output;
  hps::Serializer<std::unordered_set<int>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::UnorderedElementsAre(3, 0, -133));
}
