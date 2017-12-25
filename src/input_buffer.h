#ifndef HPS_INPUT_STREAM_H_
#define HPS_INPUT_STREAM_H_

#include <cassert>
#include <cstring>
#include <iostream>

namespace hps {

constexpr size_t INPUT_BUFFER_SIZE = 4096;
constexpr size_t INPUT_MAX_BACK = 24;

class InputBuffer {
 public:
  InputBuffer(std::istream& stream) : stream(&stream) {
    pos = 0;
    first = true;
    if (stream.fail()) stream.clear();  // Clear error bit.
    stream.seekg(0, stream.beg);
  }

  void read(char* content, const size_t length) {
    if (first) {
      stream->read(buffer, INPUT_BUFFER_SIZE);
      first = false;
    }
    if (length + pos >= INPUT_BUFFER_SIZE) {
      const size_t n_avail = INPUT_BUFFER_SIZE - pos;
      read_core(content, n_avail);
      next_trunk();
      read(content + n_avail, length - n_avail);
    } else {
      read_core(content, length);
    }
  }

  void back(const size_t n) {
    assert(pos >= n);
    pos -= n;
  }

 private:
  std::istream* const stream;

  char buffer[INPUT_BUFFER_SIZE];

  size_t pos;

  bool first;

  void read_core(char* content, const size_t length) {
    memcpy(content, buffer + pos, length);
    pos += length;
  }

  void next_trunk() {
    pos = INPUT_MAX_BACK;
    memcpy(buffer, buffer + (INPUT_BUFFER_SIZE - INPUT_MAX_BACK), INPUT_MAX_BACK);
    if (!stream->eof()) {
      stream->read(buffer + INPUT_MAX_BACK, INPUT_BUFFER_SIZE - INPUT_MAX_BACK);
    }
  }
};

}  // namespace hps

#endif