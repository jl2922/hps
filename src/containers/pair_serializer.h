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
  static void serialize(const std::pair<T1, T2>& container, std::ostream& stream) {
    Serializer<T1>::serialize(container.first, stream);
    Serializer<T2>::serialize(container.second, stream);
  }

  static void parse(std::pair<T1, T2>& container, std::istream& stream) {
    Serializer<T1>::parse(container.first, stream);
    Serializer<T2>::parse(container.second, stream);
  }
};

}  // namespace hps

#endif
