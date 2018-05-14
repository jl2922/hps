#ifndef JL2922_HPS_MAP_SERIALIZER_H
#define JL2922_HPS_MAP_SERIALIZER_H

#include <iostream>
#include <map>
#include <utility>
#include "../basic_type/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class K, class V, class B>
class Serializer<std::map<K, V>, B> {
 public:
  static void serialize(const std::map<K, V>& container, B& ob) {
    Serializer<size_t, B>::serialize(container.size(), ob);
    for (const auto& elem : container) {
      Serializer<K, B>::serialize(elem.first, ob);
      Serializer<V, B>::serialize(elem.second, ob);
    }
  }

  static void parse(std::map<K, V>& container, B& ib) {
    size_t n_elems;
    Serializer<size_t, B>::parse(n_elems, ib);
    container.clear();
    K key;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<K, B>::parse(key, ib);
      Serializer<V, B>::parse(container[std::move(key)], ib);
    }
  }
};

}  // namespace hps
#endif
