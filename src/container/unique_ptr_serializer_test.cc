#include "unique_ptr_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include "../basic_type/basic_type.h"
#include "../buffer/buffer.h"

TEST(UniquePtrSerializerTest, NoElement) {
  std::unique_ptr<std::string> input;
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::unique_ptr<std::string>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::unique_ptr<std::string> output;
  hps::Serializer<std::unique_ptr<std::string>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_FALSE(output);
}

TEST(UniquePtrSerializerTest, HasElement) {
  std::unique_ptr<std::string> input(new std::string("aaa"));
  std::stringstream ss;
  hps::StreamOutputBuffer ob(ss);
  hps::Serializer<std::unique_ptr<std::string>, hps::StreamOutputBuffer>::serialize(input, ob);
  ob.flush();

  hps::StreamInputBuffer ib(ss);
  std::unique_ptr<std::string> output;
  hps::Serializer<std::unique_ptr<std::string>, hps::StreamInputBuffer>::parse(output, ib);
  EXPECT_EQ(*(output.get()), "aaa");
}
