#ifndef HPS_PAIR_SERIALIZER_H_
#define HPS_PAIR_SERIALIZER_H_

#include <iostream>
#include <utility>
#include "../basic_types/uint_serializer.h"
#include "../serializer.h"

namespace hps {

template <class T1, class T2>
class Serializer<std::pair<T1, T2>> {
 public:
  static void serialize(const std::pair<T1, T2>& container, OutputBuffer& ob) {
    Serializer<T1>::serialize(container.first, ob);
    Serializer<T2>::serialize(container.second, ob);
  }

  static void parse(std::pair<T1, T2>& container, InputBuffer& ib) {
    Serializer<T1>::parse(container.first, ib);
    Serializer<T2>::parse(container.second, ib);
  }
};

}  // namespace hps

#endif
