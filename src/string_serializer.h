#ifndef HPS_STRING_SERIALIZER_H_
#define HPS_STRING_SERIALIZER_H_

#include <iostream>
#include <string>
#include "uint_serializer.h"

namespace hps {

void serialize(const std::string& str, std::ostream& stream) {
  const unsigned long long n_bytes = str.size();
  serialize(n_bytes, stream);
  stream.write(str.c_str(), n_bytes);
}

void parse(std::string& str, std::istream& stream) {
  unsigned long long n_bytes;
  parse(n_bytes, stream);
  char* buf = new char[n_bytes];
  stream.read(buf, n_bytes);
  str.assign(buf, n_bytes);
}

}  // namespace hps

#endif
