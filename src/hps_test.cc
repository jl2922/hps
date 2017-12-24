#include "hps.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(HpsTest, SerializeToStream) {
  const int input = 22;
  std::stringstream ss;
  hps::serialize(input, ss);
  ss.seekg(0, ss.beg);
  const int output = hps::parse<int>(ss);
  EXPECT_EQ(input, output);
}

TEST(HpsTest, SerializeToString) {
  const double input = 1.1;
  std::string str = hps::serialize_to_string(input);
  const double output = hps::parse_from_string<double>(str);
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
  friend hps::Serializer<CustomType>;
};

template <>
class hps::Serializer<CustomType> {
 public:
  static void serialize(const CustomType& obj, std::ostream& stream) {
    hps::serialize(obj.num, stream);
    hps::serialize(obj.vec, stream);
    hps::serialize(obj.str, stream);
  }

  static void parse(CustomType& obj, std::istream& stream) {
    obj.num = hps::parse<int>(stream);
    obj.vec = hps::parse<std::vector<double>>(stream);
    obj.str = hps::parse<std::string>(stream);
  }
};

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