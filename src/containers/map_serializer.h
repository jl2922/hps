#ifndef HPS_MAP_SERIALIZER_H_
#define HPS_MAP_SERIALIZER_H_

#include <iostream>
#include <map>
#include <utility>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class K, class V>
class Serializer<std::map<K, V>> {
 public:
  static void serialize(const std::map<K, V>& container, std::ostream& stream) {
    Serializer<size_t>::serialize(container.size(), stream);
    for (const auto& elem : container) {
      Serializer<K>::serialize(elem.first, stream);
      Serializer<V>::serialize(elem.second, stream);
    }
  }

  static void parse(std::map<K, V>& container, std::istream& stream) {
    size_t n_elems;
    Serializer<size_t>::parse(n_elems, stream);
    container.clear();
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
