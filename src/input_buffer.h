#ifndef HPS_INPUT_BUFFER_H_
#define HPS_INPUT_BUFFER_H_

#include <cassert>
#include <cstring>
#include <iostream>

namespace hps {

constexpr size_t INPUT_BUFFER_SIZE = 4096;

class InputBuffer {
 public:
  InputBuffer(std::istream& stream) : stream(&stream) {
    pos = 0;
    stream.seekg(0, stream.beg);
    stream.read(buffer, INPUT_BUFFER_SIZE);
  }

  void read(char* content, const size_t length) {
    if (length + pos >= INPUT_BUFFER_SIZE) {
      const size_t n_avail = INPUT_BUFFER_SIZE - pos;
      read_core(content, n_avail);
      next();
      read(content + n_avail, length - n_avail);
    } else {
      read_core(content, length);
    }
  }

  char read_char() {
    if (pos == INPUT_BUFFER_SIZE) {
      next();
    }
    const char ch = buffer[pos];
    pos++;
    return ch;
  }

 private:
  std::istream* const stream;

  char buffer[INPUT_BUFFER_SIZE];

  size_t pos;

  void read_core(char* content, const size_t length) {
    memcpy(content, buffer + pos, length);
    pos += length;
  }

  void next() {
    stream->read(buffer, INPUT_BUFFER_SIZE);
    pos = 0;
  }
};

}  // namespace hps

#endif