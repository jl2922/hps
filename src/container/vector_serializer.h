#ifndef HPS_VECTOR_SERIALIZER_H_
#define HPS_VECTOR_SERIALIZER_H_

#include <iostream>
#include <type_traits>
#include <vector>
#include "../basic_type/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T, class B>
class Serializer<
    std::vector<T>,
    B,
    typename std::enable_if<!std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const std::vector<T>& container, OutputBuffer<B>& ob) {
    Serializer<size_t, B>::serialize(container.size(), ob);
    for (const T& elem : container) {
      Serializer<T, B>::serialize(elem, ob);
    }
  }

  static void parse(std::vector<T>& container, InputBuffer<B>& ib) {
    size_t n_elems;
    Serializer<size_t, B>::parse(n_elems, ib);
    container.resize(n_elems);
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T, B>::parse(container[i], ib);
    }
  }
};

template <class T, class B>
class Serializer<
    std::vector<T>,
    B,
    typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
 public:
  static void serialize(const std::vector<T>& container, OutputBuffer<B>& ob) {
    const size_t n_elems = container.size();
    Serializer<size_t, B>::serialize(n_elems, ob);
    const char* num_ptr = reinterpret_cast<const char*>(container.data());
    ob.write(num_ptr, n_elems * sizeof(T));
  }

  static void parse(std::vector<T>& container, InputBuffer<B>& ib) {
    size_t n_elems;
    Serializer<size_t, B>::parse(n_elems, ib);
    container.resize(n_elems);
    char* num_ptr = reinterpret_cast<char*>(container.data());
    ib.read(num_ptr, n_elems * sizeof(T));
  }
};

}  // namespace hps

#endif
