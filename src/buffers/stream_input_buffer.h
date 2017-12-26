#ifndef HPS_STREAM_INPUT_BUFFER_H_
#define HPS_STREAM_INPUT_BUFFER_H_

#include <cstring>
#include <iostream>
#include "input_buffer.h"
#include "stream.h"

namespace hps {

constexpr size_t STREAM_INPUT_BUFFER_SIZE = 1 << 17;

template <>
class InputBuffer<Stream> {
 public:
  InputBuffer(std::istream& stream) : stream(&stream) {
    stream.seekg(0, stream.beg);
    load();
  }

  void read(char* content, size_t length) {
    while (pos + length > STREAM_INPUT_BUFFER_SIZE) {
      const size_t n_avail = STREAM_INPUT_BUFFER_SIZE - pos;
      read_core(content, n_avail);
      length -= n_avail;
      content += n_avail;
      load();
    }
    read_core(content, length);
  }

  char read_char() {
    if (pos == STREAM_INPUT_BUFFER_SIZE) {
      load();
    }
    const char ch = buffer[pos];
    pos++;
    return ch;
  }

 private:
  std::istream* const stream;

  char buffer[STREAM_INPUT_BUFFER_SIZE];

  size_t pos;

  void read_core(char* content, const size_t length) {
    memcpy(content, buffer + pos, length);
    pos += length;
  }

  void load() {
    stream->read(buffer, STREAM_INPUT_BUFFER_SIZE);
    pos = 0;
  }
};

}  // namespace hps

#endif
