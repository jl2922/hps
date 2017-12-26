#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <chrono>
#include <iostream>
#include "../hps.h"
#include "data.pb.h"

constexpr static unsigned long long N_ELEMS = 1 << 26;

TEST(DoubleArrayBenchmarkLargeTest, Warmup) {
  std::vector<double> origin;
  origin.resize(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    origin[i] = i + 0.1;
  }
}

TEST(DoubleArrayBenchmarkLargeTest, Protobuf) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  data::DoubleArray origin;
  origin.mutable_elems()->Reserve(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    origin.add_elems(i + 0.1);
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::string serialized;
  origin.SerializeToString(&serialized);
  data::DoubleArray parsed;
  parsed.ParseFromString(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(origin, parsed));

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(DoubleArrayBenchmarkLargeTest, BoostSerialization) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  std::vector<double> origin;
  origin.resize(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    origin[i] = i + 0.1;
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::ostringstream ostream;
  boost::archive::binary_oarchive oarchive(ostream);
  oarchive << origin;
  const std::string serialized = ostream.str();
  std::istringstream istream(serialized);
  boost::archive::binary_iarchive iarchive(istream);
  std::vector<double> parsed;
  iarchive >> parsed;

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(DoubleArrayBenchmarkLargeTest, HPS) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  std::vector<double> origin;
  origin.resize(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    origin[i] = i + 0.1;
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  const std::string serialized = hps::serialize_to_string(origin);
  auto parsed = hps::parse_from_string<std::vector<double>>(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}
