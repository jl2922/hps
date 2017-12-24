#ifndef HPS_VECTOR_SERIALIZATION_H_
#define HPS_VECTOR_SERIALIZATION_H_

#include <iostream>
#include <vector>
#include "serializer.h"
#include "uint_serializer.h"

namespace hps {

template <class T>
class Serializer<std::vector<T>> {
 public:
  static void serialize(const std::vector<T>& vec, std::ostream& stream) {
    Serializer<size_t>::serialize(vec.size(), stream);
    for (const T& elem : vec) {
      Serializer<T>::serialize(elem, stream);
    }
  }

  static void parse(std::vector<T>& vec, std::istream& stream) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, stream);
    vec.resize(n_elems);
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(vec[i], stream);
    }
  }
};

}  // namespace hps

#endif
