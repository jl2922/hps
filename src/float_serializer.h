#ifndef HPS_DOUBLE_SERIALIZER_H_
#define HPS_DOUBLE_SERIALIZER_H_

#include <iostream>
#include <type_traits>

namespace hps {

// Reinterpret floating point numbers as raw bytes array.

template <class T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type serialize(
    const T& num, std::ostream& stream) {
  const int n_bytes = sizeof(num);
  const char* num_ptr = reinterpret_cast<const char*>(&num);
  stream.write(num_ptr, n_bytes);
}

template <class T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type parse(
    T& num, std::istream& stream) {
  const int n_bytes = sizeof(num);
  char* num_ptr = reinterpret_cast<char*>(&num);
  stream.read(num_ptr, n_bytes);
}

}  // namespace hps

#endif
