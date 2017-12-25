#include "vector_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "../basic_types/int_serializer.h"
#include "../basic_types/string_serializer.h"

TEST(VectorSerializerTest, TestNoElements) {
  std::vector<int> input;
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::vector<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(VectorSerializerTest, TestFewElements) {
  std::vector<int> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::vector<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}

TEST(VectorSerializerTest, TestVectorOfVector) {
  std::vector<std::vector<int>> input;
  input.push_back(std::vector<int>({4, 44}));
  input.push_back(std::vector<int>({0}));
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::vector<std::vector<int>>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::vector<std::vector<int>> output;
  hps::Serializer<std::vector<std::vector<int>>>::parse(output, ib);
  EXPECT_EQ(output.size(), 2);
  EXPECT_THAT(output[0], testing::ElementsAre(4, 44));
  EXPECT_THAT(output[1], testing::ElementsAre(0));
}

TEST(VectorSerializerSpeedTest, TestManyIntElements) {
  std::vector<int> input;
  const int n_elems = 1 << 24;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) {
    input[i] = i;
  }
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::vector<int>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::vector<int> output;
  hps::Serializer<std::vector<int>>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(input[i], output[i]);
  }
}

TEST(VectorSerializerSpeedTest, TestManyStringElements) {
  std::vector<std::string> input;
  const int n_elems = 1 << 22;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) {
    input[i] = "fadczioupekljaiou";
  }
  std::stringstream ss;
  hps::OutputBuffer ob(ss);
  hps::Serializer<std::vector<std::string>>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer ib(ss);
  std::vector<std::string> output;
  hps::Serializer<std::vector<std::string>>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(input[i], output[i]);
  }
}