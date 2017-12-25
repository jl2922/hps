#ifndef HPS_ARRAY_SERIALIZER_H_
#define HPS_ARRAY_SERIALIZER_H_

#include <array>
#include <iostream>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T, size_t N>
class Serializer<std::array<T, N>> {
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

}  // namespace hps

#endif
