#include "hps.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(HpsTest, SerializeToAndParseFromStream) {
  const int input = 22;
  std::stringstream ss;
  hps::serialize_to_stream(input, ss);

  const int output = hps::parse_from_stream<int>(ss);
  EXPECT_EQ(input, output);
}

TEST(HpsSpeedTest, SerializeVectorsToAndFromStream) {
  const std::vector<double> input(1 << 11, 3.3);
  std::vector<double> output;
  std::stringstream ss;
  for (size_t i = 0; i < 1 << 18; i++) {
    hps::serialize_to_stream(input, ss);
    hps::parse_from_stream(output, ss);
  }
  EXPECT_EQ(input, output);
}

TEST(HpsTest, SerializeToAndParseFromString) {
  const double input = 1.1;
  std::string str = hps::serialize_to_string(input);
  const double output = hps::parse_from_string<double>(str);
  EXPECT_EQ(input, output);
}

TEST(HpsSpeedTest, SerializeVectorsToAndFromString) {
  const std::vector<double> input(1 << 11, 3.3);
  std::vector<double> output;
  for (size_t i = 0; i < 1 << 18; i++) {
    const std::string str = hps::serialize_to_string(input);
    output = hps::parse_from_string<std::vector<double>>(str);
  }
  EXPECT_EQ(input, output);
}

class CustomType {
 public:
  int num;
  std::vector<double> vec;

  void set_str(const std::string& str) { this->str = str; }
  std::string get_str() const { return str; }

 private:
  std::string str;

  // For the private member.
  template <class T, class B, class E>
  friend class hps::Serializer;
};

namespace hps {
template <class B>
class Serializer<CustomType, B> {
 public:
  static void serialize(const CustomType& obj, OutputBuffer<B>& ob) {
    Serializer<int, B>::serialize(obj.num, ob);
    Serializer<std::vector<double>, B>::serialize(obj.vec, ob);
    Serializer<std::string, B>::serialize(obj.str, ob);
  }

  static void parse(CustomType& obj, InputBuffer<B>& ib) {
    Serializer<int, B>::parse(obj.num, ib);
    Serializer<std::vector<double>, B>::parse(obj.vec, ib);
    Serializer<std::string, B>::parse(obj.str, ib);
  }
};
}  // namespace hps

TEST(HpsTest, SerializeCustomType) {
  CustomType input;
  input.num = 3;
  input.vec.push_back(2.2);
  input.vec.push_back(-4.4);
  input.set_str("aa");
  const std::string& str = hps::serialize_to_string(input);
  const CustomType& output = hps::parse_from_string<CustomType>(str);
  EXPECT_EQ(output.num, input.num);
  EXPECT_THAT(output.vec, testing::ElementsAre(2.2, -4.4));
  EXPECT_EQ(output.get_str(), "aa");
}

TEST(HpsTest, SerializeCustomTypeVector) {
  std::vector<CustomType> input(1);
  input[0].num = 3;
  input[0].vec.push_back(2.2);
  input[0].vec.push_back(-4.4);
  input[0].set_str("aa");
  const std::string& str = hps::serialize_to_string(input);
  const std::vector<CustomType>& output = hps::parse_from_string<std::vector<CustomType>>(str);
  EXPECT_EQ(output[0].num, 3);
  EXPECT_THAT(output[0].vec, testing::ElementsAre(2.2, -4.4));
  EXPECT_EQ(output[0].get_str(), "aa");
}