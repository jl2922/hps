#ifndef HPS_MAP_SERIALIZER_H_
#define HPS_MAP_SERIALIZER_H_

#include <iostream>
#include <map>
#include <utility>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class K, class V, class B>
class Serializer<std::map<K, V>, B> {
 public:
  static void serialize(const std::map<K, V>& container, OutputBuffer<B>& ob) {
    Serializer<size_t, B>::serialize(container.size(), ob);
    for (const auto& elem : container) {
      Serializer<K, B>::serialize(elem.first, ob);
      Serializer<V, B>::serialize(elem.second, ob);
    }
  }

  static void parse(std::map<K, V>& container, InputBuffer<B>& ib) {
    size_t n_elems;
    Serializer<size_t, B>::parse(n_elems, ib);
    container.clear();
    K key;
    V value;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<K, B>::parse(key, ib);
      Serializer<V, B>::parse(value, ib);
      container[std::move(key)] = std::move(value);
    }
  }
};

}  // namespace hps

#endif
