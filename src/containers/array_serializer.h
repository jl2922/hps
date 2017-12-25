#ifndef HPS_ARRAY_SERIALIZER_H_
#define HPS_ARRAY_SERIALIZER_H_

#include <array>
#include <iostream>
#include <type_traits>
#include "../serializer.h"

namespace hps {

template <class T, size_t N>
class Serializer<
    std::array<T, N>,
    typename std::enable_if<!std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const std::array<T, N>& container, OutputBuffer& ob) {
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, ob);
    }
  }

  static void parse(std::array<T, N>& container, InputBuffer& ib) {
    for (size_t i = 0; i < N; i++) {
      Serializer<T>::parse(container[i], ib);
    }
  }
};

template <class T, size_t N>
class Serializer<
    std::array<T, N>,
    typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const std::array<T, N>& container, OutputBuffer& ob) {
    const char* num_ptr = reinterpret_cast<const char*>(container.data());
    ob.write(num_ptr, N * sizeof(T));
  }

  static void parse(std::array<T, N>& container, InputBuffer& ib) {
    char* num_ptr = reinterpret_cast<char*>(container.data());
    ib.read(num_ptr, N * sizeof(T));
  }
};

}  // namespace hps

#endif
