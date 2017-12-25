#ifndef HPS_VECTOR_SERIALIZER_H_
#define HPS_VECTOR_SERIALIZER_H_

#include <iostream>
#include <vector>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T>
class Serializer<
    std::vector<T>,
    typename std::enable_if<!std::is_floating_point<T>::value, void>::type> {
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

template <class T>
class Serializer<
    std::vector<T>,
    typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const std::vector<T>& container, OutputBuffer& ob) {
    const size_t n_elems = container.size();
    Serializer<size_t>::serialize(n_elems, ob);
    const char* num_ptr = reinterpret_cast<const char*>(container.data());
    ob.write(num_ptr, n_elems * sizeof(T));
  }

  static void parse(std::vector<T>& container, InputBuffer& ib) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, ib);
    container.resize(n_elems);
    char* num_ptr = reinterpret_cast<char*>(container.data());
    ib.read(num_ptr, n_elems * sizeof(T));
  }
};

}  // namespace hps

#endif
