#include "unique_ptr_serializer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include "../basic_type/basic_type.h"

TEST(UniquePtrSerializerTest, NoElement) {
  std::unique_ptr<std::string> input;
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::unique_ptr<std::string>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::unique_ptr<std::string> output;
  hps::Serializer<std::unique_ptr<std::string>, hps::Stream>::parse(output, ib);
  EXPECT_FALSE(output);
}

TEST(UniquePtrSerializerTest, HasElement) {
  std::unique_ptr<std::string> input(new std::string("aaa"));
  std::stringstream ss;
  hps::OutputBuffer<hps::Stream> ob(ss);
  hps::Serializer<std::unique_ptr<std::string>, hps::Stream>::serialize(input, ob);
  ob.flush();

  hps::InputBuffer<hps::Stream> ib(ss);
  std::unique_ptr<std::string> output;
  hps::Serializer<std::unique_ptr<std::string>, hps::Stream>::parse(output, ib);
  EXPECT_EQ(*(output.get()), "aaa");
}
