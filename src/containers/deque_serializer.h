#ifndef HPS_DEQUE_SERIALIZER_H_
#define HPS_DEQUE_SERIALIZER_H_

#include <iostream>
#include <deque>
#include <utility>
#include "../serializer.h"
#include "../basic_types/uint_serializer.h"

namespace hps {

template <class T>
class Serializer<std::deque<T>> {
 public:
  static void serialize(const std::deque<T>& container, std::ostream& stream) {
    Serializer<size_t>::serialize(container.size(), stream);
    for (const T& elem : container) {
      Serializer<T>::serialize(elem, stream);
    }
  }

  static void parse(std::deque<T>& container, std::istream& stream) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, stream);
    container.clear();
    T elem;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<T>::parse(elem, stream);
      container.push_back(std::move(elem));
    }
  }
};

}  // namespace hps

#endif
