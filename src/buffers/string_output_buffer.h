#ifndef HPS_STRING_OUTPUT_BUFFER_H_
#define HPS_STRING_OUTPUT_BUFFER_H_

#include <string>
#include "output_buffer.h"

namespace hps {

template <>
class OutputBuffer<std::string> {
 public:
  OutputBuffer(std::string& str) : str(&str) {}

  void write(const char* content, size_t length) { str->append(content, length); }

  void write_char(const char ch) { str->push_back(ch); }

 private:
  std::string* const str;
};

}  // namespace hps

#endif
