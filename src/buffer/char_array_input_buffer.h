#pragma once

#include <cstring>
#include "input_buffer.h"

namespace hps {

template <>
class InputBuffer<char*> {
 public:
  InputBuffer(const char* arr) : arr(arr) { pos = 0; }

  void read(char* content, size_t length) {
    strncpy(content, &arr[pos], length);
    pos += length;
  }

  char read_char() {
    const char ch = arr[pos];
    pos++;
    return ch;
  }

 private:
  const char* const arr;

  size_t pos;
};

}  // namespace hps
