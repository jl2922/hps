#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "int_serializer.h"

#include "vector_serialization.h"

TEST(VectorSerializationTest, TestNoElements) {
  std::vector<int> input;
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(VectorSerializationTest, TestFewElements) {
  std::vector<int> input;
  input.push_back(3);
  input.push_back(-5);
  input.push_back(150);
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::parse(output, ss);
  EXPECT_THAT(output, testing::ElementsAre(3, -5, 150));
}

TEST(VectorSerializationTest, TestVectorOfVector) {
  std::vector<std::vector<int>> input;
  input.push_back(std::vector<int>({4, -88}));
  input.push_back(std::vector<int>({0, }));
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<std::vector<int>> output;
  hps::parse(output, ss);
  EXPECT_EQ(output.size(), 2);
  EXPECT_THAT(output[0], testing::ElementsAre(4, -88));
  EXPECT_THAT(output[1], testing::ElementsAre(0));
}

TEST(VectorSerializationSpeedTest, TestManyElements) {
  std::vector<int> input;
  const int n_elems = 1 << 22;
  input.reserve(n_elems);
  for (int i = 0; i < n_elems; i++) {
    input.push_back(i);
  }
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<int> output;
  hps::parse(output, ss);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(input[i], output[i]);
  }
}