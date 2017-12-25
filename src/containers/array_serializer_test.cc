#include "array_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <array>
#include "../basic_types/float_serializer.h"
#include "../basic_types/int_serializer.h"

TEST(ArraySerializerTest, TestFewInts) {
  std::array<int, 3> input{{3, 444, -33}};
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::array<int, 3>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::array<int, 3> output;
  hps::Serializer<std::array<int, 3>>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 444, -33));
}

TEST(ArraySerializerTest, TestFewDoubles) {
  std::array<double, 3> input{{3, 4.44, -3.3}};
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::array<double, 3>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::array<double, 3> output;
  hps::Serializer<std::array<double, 3>>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 4.44, -3.3));
}
