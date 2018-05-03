#include <capnp/message.h>
#include <capnp/serialize.h>
#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <chrono>
#include <iostream>
#include "../hps.h"
#include "capnproto_benchmark.capnp.h"
#include "protobuf_benchmark.pb.h"

constexpr static unsigned long long N_ENTRIES = 1 << 23;

TEST(MapBenchmarkLargeTest, Warmup) {
  std::unordered_map<std::string, double> origin;
  origin.reserve(N_ENTRIES);
  for (unsigned long long i = 0; i < N_ENTRIES; i++) {
    origin["key-" + std::to_string(i)] = i + 0.1;
  }
}

TEST(MapBenchmarkLargeTest, Protobuf) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  protobuf_benchmark::Map origin;
  auto entries = origin.mutable_entries();
  for (unsigned long long i = 0; i < N_ENTRIES; i++) {
    (*entries)["key-" + std::to_string(i)] = i + 0.1;
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::string serialized;
  origin.SerializeToString(&serialized);
  protobuf_benchmark::Map parsed;
  parsed.ParseFromString(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin.entries_size(), parsed.entries_size()); // Item by item comparison is too slow.

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(MapBenchmarkLargeTest, BoostSerialization) {
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
  std::ostringstream ostream;
  boost::archive::binary_oarchive oarchive(ostream);
  oarchive << origin;
  const std::string serialized = ostream.str();
  std::istringstream istream(serialized);
  boost::archive::binary_iarchive iarchive(istream);
  std::unordered_map<std::string, double> parsed;
  iarchive >> parsed;

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(MapBenchmarkLargeTest, HPS) {
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
