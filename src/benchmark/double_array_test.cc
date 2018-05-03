#include <capnp/message.h>
#include <capnp/serialize.h>
#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>
#include <sys/mman.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <chrono>
#include <iostream>
#include "../hps.h"
#include "capnproto_benchmark.capnp.h"
#include "protobuf_benchmark.pb.h"

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
  protobuf_benchmark::DoubleArray origin;
  origin.mutable_elems()->Reserve(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    origin.add_elems(i + 0.1);
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::string serialized;
  origin.SerializeToString(&serialized);
  protobuf_benchmark::DoubleArray parsed;
  parsed.ParseFromString(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(origin, parsed));

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(DoubleArrayBenchmarkLargeTest, CapnProto) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  capnp::MallocMessageBuilder origin_builder;
  capnproto_benchmark::DoubleArray::Builder origin =
      origin_builder.getRoot<capnproto_benchmark::DoubleArray>();
  auto elems = origin.initElems(N_ELEMS);
  for (unsigned long long i = 0; i < N_ELEMS; i++) {
    elems.set(i, i + 0.1);
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  auto serialized = messageToFlatArray(origin_builder);
  capnp::ReaderOptions options;
  options.traversalLimitInWords = 1ull << 60;
  capnp::MallocMessageBuilder parsed_builder;
  capnp::initMessageBuilderFromFlatArrayCopy(serialized, parsed_builder, options);

  auto finish_time = high_resolution_clock::now();

  capnproto_benchmark::DoubleArray::Reader parsed =
      parsed_builder.getRoot<capnproto_benchmark::DoubleArray>();
  EXPECT_EQ(parsed.getElems().size(), N_ELEMS);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.asChars().size() << std::endl;
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
  const std::string serialized = hps::to_string(origin);
  auto parsed = hps::from_string<std::vector<double>>(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}
