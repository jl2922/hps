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
  static void serialize(const std::vector<T>& container, OutputBuffer& ob) {
    Serializer<size_t>::serialize(container.size(), ob);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, ob);
    }
  }

  static void parse(std::vector<T>& container, InputBuffer& ib) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, ib);
    container.resize(n_elems);
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(container[i], ib);
    }
  }
};

}  // namespace hps

#endif
