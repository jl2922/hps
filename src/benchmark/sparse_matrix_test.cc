#include <capnp/message.h>
#include <capnp/serialize.h>
#include <google/protobuf/util/message_differencer.h>
#include <gtest/gtest.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <chrono>
#include <iostream>
#include "../hps.h"
#include "capnproto_benchmark.capnp.h"
#include "protobuf_benchmark.pb.h"

constexpr static unsigned long long N_ROWS = 1 << 15;
constexpr static unsigned long long N_NONZERO_COLS = 1 << 10;

TEST(SparseMatrixBenchmarkLargeTest, Warmup) {
  using SparseMatrix =
      typename std::vector<std::pair<std::vector<unsigned long long>, std::vector<double>>>;
  SparseMatrix origin;
  origin.resize(N_ROWS);
  for (unsigned long long i = 0; i < N_ROWS; i++) {
    origin[i].first.resize(N_NONZERO_COLS);
    origin[i].second.resize(N_NONZERO_COLS);
    for (unsigned long long j = 0; j < N_NONZERO_COLS; j++) {
      origin[i].first[j] = i + j;
      origin[i].second[j] = i + j + 0.1;
    }
  }
}

TEST(SparseMatrixBenchmarkLargeTest, Protobuf) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  protobuf_benchmark::SparseMatrix origin;
  origin.mutable_rows()->Reserve(N_ROWS);
  for (unsigned long long i = 0; i < N_ROWS; i++) {
    protobuf_benchmark::SparseMatrixRow* row = origin.add_rows();
    row->mutable_cols()->Reserve(N_NONZERO_COLS);
    row->mutable_values()->Reserve(N_NONZERO_COLS);
    for (unsigned long long j = 0; j < N_NONZERO_COLS; j++) {
      row->add_cols(i + j);
      row->add_values(i + j + 0.1);
    }
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::string serialized;
  origin.SerializeToString(&serialized);
  protobuf_benchmark::SparseMatrix parsed;
  parsed.ParseFromString(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(origin, parsed));

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(SparseMatrixBenchmarkLargeTest, CapnProto) {
  using namespace std::chrono;

  auto start_time = high_resolution_clock::now();

  // Construct.
  capnp::MallocMessageBuilder message_builder;
  capnproto_benchmark::SparseMatrix::Builder origin =
      message_builder.getRoot<capnproto_benchmark::SparseMatrix>();
  auto rows = origin.initRows(N_ROWS);
  for (unsigned long long i = 0; i < N_ROWS; i++) {
    auto row = rows[i];
    auto cols = row.initCols(N_NONZERO_COLS);
    auto values = row.initValues(N_NONZERO_COLS);
    for (unsigned long long j = 0; j < N_NONZERO_COLS; j++) {
      cols.set(j, i + j);
      values.set(j, i + j + 0.1);
    }
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  auto serialized = messageToFlatArray(message_builder);
  capnp::ReaderOptions options;
  options.traversalLimitInWords = 1ull << 60;
  capnp::MallocMessageBuilder parsed_builder;
  capnp::initMessageBuilderFromFlatArrayCopy(serialized, parsed_builder, options);

  auto finish_time = high_resolution_clock::now();

  capnproto_benchmark::SparseMatrix::Reader parsed =
      parsed_builder.getRoot<capnproto_benchmark::SparseMatrix>();
  EXPECT_EQ(parsed.getRows().size(), N_ROWS);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.asChars().size() << std::endl;
}

TEST(SparseMatrixBenchmarkLargeTest, BoostSerialization) {
  using namespace std::chrono;
  using SparseMatrix =
      typename std::vector<std::pair<std::vector<unsigned long long>, std::vector<double>>>;

  auto start_time = high_resolution_clock::now();

  // Construct.
  SparseMatrix origin;
  origin.resize(N_ROWS);
  for (unsigned long long i = 0; i < N_ROWS; i++) {
    origin[i].first.resize(N_NONZERO_COLS);
    origin[i].second.resize(N_NONZERO_COLS);
    for (unsigned long long j = 0; j < N_NONZERO_COLS; j++) {
      origin[i].first[j] = i + j;
      origin[i].second[j] = i + j + 0.1;
    }
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::ostringstream ostream;
  boost::archive::binary_oarchive oarchive(ostream);
  oarchive << origin;
  const std::string serialized = ostream.str();
  std::istringstream istream(serialized);
  boost::archive::binary_iarchive iarchive(istream);
  SparseMatrix parsed;
  iarchive >> parsed;

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}

TEST(SparseMatrixBenchmarkLargeTest, HPS) {
  using namespace std::chrono;
  using SparseMatrix =
      typename std::vector<std::pair<std::vector<unsigned long long>, std::vector<double>>>;

  auto start_time = high_resolution_clock::now();

  // Construct.
  SparseMatrix origin;
  origin.resize(N_ROWS);
  for (unsigned long long i = 0; i < N_ROWS; i++) {
    origin[i].first.resize(N_NONZERO_COLS);
    origin[i].second.resize(N_NONZERO_COLS);
    for (unsigned long long j = 0; j < N_NONZERO_COLS; j++) {
      origin[i].first[j] = i + j;
      origin[i].second[j] = i + j + 0.1;
    }
  }

  auto constructed_time = high_resolution_clock::now();

  // Serialize and parse.
  std::string serialized;
  hps::to_string(origin, serialized);
  auto parsed = hps::from_string<SparseMatrix>(serialized);

  auto finish_time = high_resolution_clock::now();

  EXPECT_EQ(origin, parsed);

  auto construction_time = duration_cast<milliseconds>(constructed_time - start_time).count();
  auto serialization_time = duration_cast<milliseconds>(finish_time - constructed_time).count();
  std::cout << "Construction Time (ms): " << construction_time << std::endl;
  std::cout << "Serialization and Parse Time (ms): " << serialization_time << std::endl;
  std::cout << "Size (B): " << serialized.size() << std::endl;
}
