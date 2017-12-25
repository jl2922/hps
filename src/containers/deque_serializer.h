#ifndef HPS_DEQUE_SERIALIZER_H_
#define HPS_DEQUE_SERIALIZER_H_

#include <deque>
#include <iostream>
#include <utility>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T>
class Serializer<std::deque<T>> {
 public:
  static void serialize(const std::deque<T>& container, OutputBuffer& ob) {
    Serializer<size_t>::serialize(container.size(), ob);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, ob);
    }
  }

  static void parse(std::deque<T>& container, InputBuffer& ib) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, ib);
    container.clear();
    T elem;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(elem, ib);
      container.push_back(std::move(elem));
    }
  }
};

}  // namespace hps

#endif
