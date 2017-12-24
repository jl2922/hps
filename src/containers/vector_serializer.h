#ifndef HPS_VECTOR_SERIALIZER_H_
#define HPS_VECTOR_SERIALIZER_H_

#include <iostream>
#include <vector>
#include "../serializer.h"
#include "../basic_types/uint_serializer.h"

namespace hps {

template <class T>
class Serializer<std::vector<T>> {
 public:
  static void serialize(const std::vector<T>& container, std::ostream& stream) {
    Serializer<size_t>::serialize(container.size(), stream);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, stream);
    }
  }

  static void parse(std::vector<T>& container, std::istream& stream) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, stream);
    container.resize(n_elems);
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(container[i], stream);
    }
  }
};

}  // namespace hps

#endif
