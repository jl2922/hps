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
  static void serialize(const std::string& str, OutputBuffer& ob) {
    const size_t n_bytes = str.size();
    Serializer<size_t>::serialize(n_bytes, ob);
    ob.write(str.c_str(), n_bytes);
  }

  static void parse(std::string& str, InputBuffer& ib) {
    size_t n_bytes;
    Serializer<size_t>::parse(n_bytes, ib);
    char buf[PARSE_BUFFER_SIZE];
    str.clear();
    str.reserve(n_bytes);
    while (n_bytes > 0) {
      if (n_bytes > PARSE_BUFFER_SIZE) {
        ib.read(buf, PARSE_BUFFER_SIZE);
        str.append(buf, PARSE_BUFFER_SIZE);
        n_bytes -= PARSE_BUFFER_SIZE;
      } else {
        ib.read(buf, n_bytes);
        str.append(buf, n_bytes);
        n_bytes = 0;
      }
    }
  }

 private:
  constexpr static size_t PARSE_BUFFER_SIZE = 1 << 8;
};

}  // namespace hps

#endif
