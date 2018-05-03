#include "unordered_map_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unordered_map>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(UnorderedMapSerializerTest, NoElements) {
  std::unordered_map<std::string, int> input;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::unordered_map<std::string, int>, hps::StreamOutputBuffer>::serialize(
      input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::unordered_map<std::string, int> output;
  hps::Serializer<std::unordered_map<std::string, int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_THAT(output, testing::IsEmpty());
}

#include <chrono>
#include "../hps.h"
TEST(UnorderedMapSerializerTest, FewElements) {
  std::unordered_map<std::string, int> input;
  input["aa"] = 33;
  input["bb"] = 0;
  input["cc"] = -333;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::unordered_map<std::string, int>, hps::StreamOutputBuffer>::serialize(
      input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::unordered_map<std::string, int> output;
  hps::Serializer<std::unordered_map<std::string, int>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(output.size(), input.size());
  EXPECT_THAT(output, testing::Contains(testing::Key("aa")));
  EXPECT_THAT(output, testing::Contains(testing::Key("bb")));
  EXPECT_THAT(output, testing::Contains(testing::Key("cc")));
  EXPECT_EQ(input.at("aa"), output.at("aa"));
  EXPECT_EQ(input.at("bb"), output.at("bb"));
  EXPECT_EQ(input.at("cc"), output.at("cc"));
}


constexpr static unsigned long long N_ENTRIES = 1 << 24;
TEST(MapBenchmarkTest, HPS) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  std::unordered_map<std::string, double> origin;
  origin.reserve(N_ENTRIES);
  for (unsigned long long i = 0; i < N_ENTRIES; i++) {
    origin["key-" + std::to_string(i)] = i + 0.1;
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  const std::string serialized = hps::to_string(origin);
  auto parsed = hps::from_string<std::unordered_map<std::string, double>>(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}
