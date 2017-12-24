#include "vector_serialization.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "uint_serializer.h"

TEST(VectorSerializationTest, TestNoElements) {
  std::vector<unsigned int> input;
  std::stringstream ss;
  hps::Serializer<std::vector<unsigned int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<unsigned int> output;
  hps::Serializer<std::vector<unsigned int>>::parse(output, ss);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(VectorSerializationTest, TestFewElements) {
  std::vector<unsigned int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(133);
  std::stringstream ss;
  hps::Serializer<std::vector<unsigned int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<unsigned int> output;
  hps::Serializer<std::vector<unsigned int>>::parse(output, ss);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, 133));
}

TEST(VectorSerializationTest, TestVectorOfVector) {
  std::vector<std::vector<unsigned int>> input;
  input.push_back(std::vector<unsigned int>({4, 44}));
  input.push_back(std::vector<unsigned int>({0}));
  std::stringstream ss;
  hps::Serializer<std::vector<std::vector<unsigned int>>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<std::vector<unsigned int>> output;
  hps::Serializer<std::vector<std::vector<unsigned int>>>::parse(output, ss);
  EXPECT_EQ(output.size(), 2);
  EXPECT_THAT(output[0], testing::ElementsAre(4, 44));
  EXPECT_THAT(output[1], testing::ElementsAre(0));
}

TEST(VectorSerializationSpeedTest, TestManyElements) {
  std::vector<unsigned int> input;
  const unsigned int n_elems = 1 << 22;
  input.reserve(n_elems);
  for (unsigned int i = 0; i < n_elems; i++) {
    input.push_back(i);
  }
  std::stringstream ss;
  hps::Serializer<std::vector<unsigned int>>::serialize(input, ss);
  ss.seekg(0, ss.beg);
  std::vector<unsigned int> output;
  hps::Serializer<std::vector<unsigned int>>::parse(output, ss);
  EXPECT_EQ(input.size(), output.size());
  for (unsigned int i = 0; i < 10; i++) {
    EXPECT_EQ(input[i], output[i]);
  }
}
