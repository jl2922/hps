#ifndef HPS_INT_SERIALIZER_H_
#define HPS_INT_SERIALIZER_H_

#include <cassert>
#include <iostream>
#include <type_traits>
#include "uint_serializer.h"

namespace hps {

// Serialize and parse unsigned integer types with base 127 zigzag encoding.

template <class T>
typename std::enable_if<std::is_signed<T>::value, void>::type serialize(
    const T& num, std::ostream& stream) {
  const int n_bits = sizeof(num) * 8;
  unsigned long long zigzaged_num = (num << 1) ^ (num >> (n_bits - 1));
  serialize(zigzaged_num, stream);
}

template <class T>
typename std::enable_if<std::is_signed<T>::value, void>::type parse(
    T& num, std::istream& stream) {
  unsigned long long zigzaged_num;
  parse(zigzaged_num, stream);
  num = (-(zigzaged_num & 1)) ^ (zigzaged_num >> 1);
}

}  // namespace hps

#endif
