#ifndef HPS_UNORDERED_MAP_SERIALIZER_H_
#define HPS_UNORDERED_MAP_SERIALIZER_H_

#include <iostream>
#include <unordered_map>
#include <utility>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class K, class V>
class Serializer<std::unordered_map<K, V>> {
 public:
  static void serialize(const std::unordered_map<K, V>& container, std::ostream& stream) {
    Serializer<size_t>::serialize(container.size(), stream);
    for (const auto& elem : container) {
      Serializer<K>::serialize(elem.first, stream);
      Serializer<V>::serialize(elem.second, stream);
    }
  }

  static void parse(std::unordered_map<K, V>& container, std::istream& stream) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, stream);
    container.clear();
    container.reserve(n_elems);
    K key;
    V value;
    for (size_t i = 0; i < n_elems; i++) {
      Serializer<K>::parse(key, stream);
      Serializer<V>::parse(value, stream);
      container[std::move(key)] = std::move(value);
    }
  }
};

}  // namespace hps

#endif
