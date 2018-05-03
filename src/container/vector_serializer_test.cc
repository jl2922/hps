#include "vector_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(VectorSerializerTest, NoElements) {
  std::vector<int> input;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<int> output;
  hps::Serializer<std::vector<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

TEST(VectorSerializerTest, FewElements) {
  std::vector<long long> input;
  input.push_back(3);
  input.push_back(0);
  input.push_back(-133);
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<long long>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<long long> output;
  hps::Serializer<std::vector<long long>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::ElementsAre(3, 0, -133));
}

TEST(VectorSerializerTest, VectorOfVector) {
  std::vector<std::vector<int>> input;
  input.push_back(std::vector<int>({4, 44}));
  input.push_back(std::vector<int>({0}));
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<std::vector<int>>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<std::vector<int>> output;
  hps::Serializer<std::vector<std::vector<int>>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(output.size(), 2);
  EXPECT_THAT(output[0], testing::ElementsAre(4, 44));
  EXPECT_THAT(output[1], testing::ElementsAre(0));
}

TEST(VectorSerializerTest, BoolElements) {
  std::vector<bool> input;
  const int n_elems = 1 << 10;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) input[i] = (i < 10 || i % 10 == 0) ? 1 : 0;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<bool>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<bool> output;
  hps::Serializer<std::vector<bool>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input, output);
  EXPECT_THAT(ss.str(), testing::SizeIs(testing::Le((n_elems << 3) + 4)));
}

TEST(VectorSerializerTest, UniquePtrElements) {
  std::vector<std::unique_ptr<int>> input;
  const int n_elems = 1 << 10;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i += 3) input[i].reset(new int(i >> 4));
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<std::unique_ptr<int>>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<std::unique_ptr<int>> output;
  hps::Serializer<std::vector<std::unique_ptr<int>>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < n_elems; i++) {
    if (input[i]) {
      EXPECT_TRUE(output[i]);
      EXPECT_EQ(*input[i], *output[i]);
    } else {
      EXPECT_FALSE(output[i]);
    }
  }
  EXPECT_THAT(ss.str(), testing::SizeIs(testing::Le((n_elems / 2))));
}

TEST(VectorSerializerLargeTest, ManyIntElements) {
  std::vector<int> input;
  const int n_elems = 1 << 25;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) input[i] = i;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<int>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<int> output;
  hps::Serializer<std::vector<int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(input[i], output[i]);
}

TEST(VectorSerializerLargeTest, ManyDoubleElements) {
  std::vector<double> input;
  const int n_elems = 1 << 25;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) input[i] = i;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<double>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<double> output;
  hps::Serializer<std::vector<double>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(input[i], output[i]);
}

TEST(VectorSerializerLargeTest, ManyStringElements) {
  std::vector<std::string> input;
  const int n_elems = 1 << 23;
  input.resize(n_elems);
  for (int i = 0; i < n_elems; i++) input[i] = "fadczioupekljaiou";
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::vector<std::string>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::vector<std::string> output;
  hps::Serializer<std::vector<std::string>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(input.size(), output.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(input[i], output[i]);
}
