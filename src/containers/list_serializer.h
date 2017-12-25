#ifndef HPS_LIST_SERIALIZER_H_
#define HPS_LIST_SERIALIZER_H_

#include <iostream>
#include <list>
#include <utility>
#include "../serializer.h"
#include "../basic_types/uint_serializer.h"

namespace hps {

template <class T>
class Serializer<std::list<T>> {
 public:
  static void serialize(const std::list<T>& container, OutputBuffer& ob) {
    Serializer<size_t>::serialize(container.size(), ob);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, ob);
    }
  }

  static void parse(std::list<T>& container, InputBuffer& ib) {
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
