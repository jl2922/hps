#include "array_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <array>
#include "../basic_type/basic_type.h"

TEST(ArraySerializerTest, FewInts) {
  std::array<int, 3> input{{3, 444, -33}};
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::array<int, 3>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::array<int, 3> output;
  hps::Serializer<std::array<int, 3>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 444, -33));
}

TEST(ArraySerializerTest, FewDoubles) {
  std::array<double, 3> input{{3, 4.44, -3.3}};
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::array<double, 3>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::array<double, 3> output;
  hps::Serializer<std::array<double, 3>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 4.44, -3.3));
}

TEST(ArraySerializerTest, FewBools) {
  std::array<bool, 3> input{{true, false, true}};
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::array<bool, 3>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::array<bool, 3> output;
  hps::Serializer<std::array<bool, 3>, hps::Stream>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(true, false, true));
  EXPECT_THAT(ss.str(), testing::SizeIs(testing::Eq(1)));
}
