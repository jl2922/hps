#include "array_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <array>
#include "../basic_types/int_serializer.h"

TEST(ArraySerializerTest, TestNormalArray) {
  std::array<int, 3> input{{3, 444, -33}};
  std::stringstream ss;
  hps::Serializer<std::array<int, 3>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::array<int, 3> output;
  hps::Serializer<std::array<int, 3>>::parse(output, ss);
  EXPECT_THAT(output, testing::ElementsAre(3, 444, -33));
}
