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
  static void serialize(const std::array<T, N>& container, std::ostream& stream) {
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, stream);
    }
  }

  static void parse(std::array<T, N>& container, std::istream& stream) {
    for (size_t i = 0; i < N; i++) {
      Serializer<T>::parse(container[i], stream);
    }
  }
};

}  // namespace hps

#endif
