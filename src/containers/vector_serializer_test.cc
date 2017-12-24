#include "vector_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "../basic_types/int_serializer.h"

TEST(VectorSerializerTest, TestNoElements) {
  std::vector<int> input;
  std::stringstream ss;
  hps::Serializer<std::vector<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(VectorSerializerTest, TestFewElements) {
  std::vector<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::Serializer<std::vector<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ss);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}

TEST(VectorSerializerTest, TestVectorOfVector) {
  std::vector<std::vector<int>> input;
  input.push_back(std::vector<int>({4, 44}));
  input.push_back(std::vector<int>({0}));
  std::stringstream ss;
  hps::Serializer<std::vector<std::vector<int>>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<std::vector<int>> output;
  hps::Serializer<std::vector<std::vector<int>>>::parse(output, ss);
  EXPECT_EQ(output.size(), 2);
  EXPECT_THAT(output[0], testing::ElementsAre(4, 44));
  EXPECT_THAT(output[1], testing::ElementsAre(0));
}

TEST(VectorSerializerSpeedTest, TestManyElements) {
  std::vector<int> input;
  const int n_elems = 1 << 22;
  input.reserve(n_elems);
  for (int i = 0; i < n_elems; i++) {
    input.push_back(i);
  }
  std::stringstream ss;
  hps::Serializer<std::vector<int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ss);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(input[i], output[i]);
  }
}
