#ifndef HPS_DOUBLE_SERIALIZER_H_
#define HPS_DOUBLE_SERIALIZER_H_

#include <iostream>
#include <type_traits>
#include "serializer.h"

namespace hps {

// Reinterpret floating point numbers as raw bytes array.

template <class T>
class Serializer<T, typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const T& num, std::ostream& stream) {
    const char* num_ptr = reinterpret_cast<const char*>(&num);
    stream.write(num_ptr, sizeof(num));
  }

  static void parse(T& num, std::istream& stream) {
    char* num_ptr = reinterpret_cast<char*>(&num);
    stream.read(num_ptr, sizeof(num));
  }
};

}  // namespace hps

#endif
