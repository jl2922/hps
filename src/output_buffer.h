#ifndef HPS_OUTPUT_BUFFER_H_
#define HPS_OUTPUT_BUFFER_H_

#include <cstring>
#include <iostream>

// #define HPS_INPUT_BUFFER_SIZE 8192

namespace hps {

constexpr size_t OUTPUT_BUFFER_SIZE = 1 << 17;

class OutputBuffer {
 public:
  OutputBuffer(std::ostream& stream) : stream(&stream) { pos = 0; }

  void write(const char* content, size_t length) {
    while (pos + length > OUTPUT_BUFFER_SIZE) {
      const size_t n_avail = OUTPUT_BUFFER_SIZE - pos;
      write_core(content, n_avail);
      flush();
      length -= n_avail;
      content += n_avail;
    }
    write_core(content, length);
  }

  void write_char(const char ch) {
    if (pos == OUTPUT_BUFFER_SIZE) {
      flush();
    }
    buffer[pos] = ch;
    pos++;
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