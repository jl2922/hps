#ifndef HPS_INT_SERIALIZER_H_
#define HPS_INT_SERIALIZER_H_

#include <iostream>
#include <type_traits>
#include "uint_serializer.h"

namespace hps {

// Serialize and parse with unsigned integer serializer through zigzag encoding.

template <class T>
class Serializer<
    T,
    typename std::enable_if<std::is_signed<T>::value && std::is_integral<T>::value, void>::type> {
 public:
  static void serialize(const T& num, OutputBuffer& ob) {
    const size_t n_bits = sizeof(num) * 8;
    using UT = typename std::make_unsigned<T>::type;
    UT zigzaged_num = (num << 1) ^ (num >> (n_bits - 1));
    Serializer<UT>::serialize(zigzaged_num, ob);
  }

  static void parse(T& num, InputBuffer& ib) {
    using UT = typename std::make_unsigned<T>::type;
    UT zigzaged_num;
    Serializer<UT>::parse(zigzaged_num, ib);
    num = (-(zigzaged_num & 1)) ^ (zigzaged_num >> 1);
  }
};

}  // namespace hps

#endif
