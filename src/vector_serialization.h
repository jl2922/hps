#ifndef HPS_VECTOR_SERIALIZATION_H_
#define HPS_VECTOR_SERIALIZATION_H_

#include <iostream>
#include <vector>
#include "uint_serializer.h"

namespace hps {

template <class T>
void serialize(const std::vector<T>& vec, std::ostream& stream) {
  serialize(vec.size(), stream);
  for (const T& elem : vec) {
    serialize(elem, stream);
  }
}

template <class T>
void parse(std::vector<T>& vec, std::istream& stream) {
  unsigned long long n_elems;
  parse(n_elems, stream);
  vec.resize(n_elems);
  for (unsigned long long i = 0; i < n_elems; i++) {
    parse(vec[i], stream);
  }
}

}  // namespace hps

#endif
