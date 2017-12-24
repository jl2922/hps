#ifndef HPS_STRING_SERIALIZER_H_
#define HPS_STRING_SERIALIZER_H_

#include <iostream>
#include <string>
#include "../serializer.h"
#include "uint_serializer.h"

namespace hps {

template <>
class Serializer<std::string> {
 public:
  static void serialize(const std::string& str, std::ostream& stream) {
    const size_t n_bytes = str.size();
    Serializer<size_t>::serialize(n_bytes, stream);
    stream.write(str.c_str(), n_bytes);
  }

  static void parse(std::string& str, std::istream& stream) {
    size_t n_bytes;
    Serializer<size_t>::parse(n_bytes, stream);
    char* buf = new char[n_bytes];
    stream.read(buf, n_bytes);
    str.assign(buf, n_bytes);
  }
};

}  // namespace hps

#endif
