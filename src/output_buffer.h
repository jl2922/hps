#ifndef HPS_OUTPUT_STREAM_H_
#define HPS_OUTPUT_STREAM_H_

#include <cstring>
#include <iostream>

// #define HPS_INPUT_BUFFER_SIZE 8192

namespace hps {

constexpr size_t OUTPUT_BUFFER_SIZE = 4096;

class OutputBuffer {
 public:
  OutputBuffer(std::ostream& stream) : stream(&stream) { pos = 0; }

  void write(const char* content, const size_t length) {
    if (pos + length > OUTPUT_BUFFER_SIZE) {
      const size_t n_avail = OUTPUT_BUFFER_SIZE - pos;
      write_core(content, n_avail);
      flush();
      write(content + n_avail, length - n_avail);
    } else {
      write_core(content, length);
    }
  }

  void flush() {
    stream->write(buffer, pos);
    pos = 0;
  }

 private:
  std::ostream* const stream;

  char buffer[OUTPUT_BUFFER_SIZE];

  int pos;

  void write_core(const char* content, const size_t length) {
    memcpy(buffer + pos, content, length);
    pos += length;
  }
};

}  // namespace hps

#endif