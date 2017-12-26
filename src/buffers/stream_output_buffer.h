#ifndef HPS_STREAM_OUTPUT_BUFFER_H_
#define HPS_STREAM_OUTPUT_BUFFER_H_

#include <cstring>
#include <iostream>
#include "output_buffer.h"
#include "stream.h"

namespace hps {

constexpr size_t STREAM_OUTPUT_BUFFER_SIZE = 1 << 14;

template <>
class OutputBuffer<Stream> {
 public:
  OutputBuffer(std::ostream& stream) : stream(&stream) { pos = 0; }

  void write(const char* content, size_t length) {
    if (pos + length > STREAM_OUTPUT_BUFFER_SIZE) {
      const size_t n_avail = STREAM_OUTPUT_BUFFER_SIZE - pos;
      write_core(content, n_avail);
      length -= n_avail;
      content += n_avail;
      flush();
      if (length > STREAM_OUTPUT_BUFFER_SIZE) {
        stream->write(content, length);
        return;
      }
    }
    write_core(content, length);
  }

  void write_char(const char ch) {
    if (pos == STREAM_OUTPUT_BUFFER_SIZE) {
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

  char buffer[STREAM_OUTPUT_BUFFER_SIZE];

  int pos;

  void write_core(const char* content, const size_t length) {
    memcpy(buffer + pos, content, length);
    pos += length;
  }
};

}  // namespace hps

#endif
