#pragma once

#include <string>
#include "input_buffer.h"

namespace hps {

template <>
class InputBuffer<std::string> {
 public:
  InputBuffer(const std::string& str) : str(&str) { pos = 0; }

  void read(char* content, size_t length) {
    str->copy(content, length, pos);
    pos += length;
  }

  char read_char() {
    const char ch = (*str)[pos];
    pos++;
    return ch;
  }

 private:
  const std::string* const str;

  size_t pos;
};

}  // namespace hps
