#ifndef HPS_UINT_SERIALIZER_H_
#define HPS_UINT_SERIALIZER_H_

#include <cassert>
#include <iostream>
#include <type_traits>
#include "../serializer.h"

namespace hps {

// Serialize and parse unsigned integer types with base 127 encoding.

template <class T>
class Serializer<T, typename std::enable_if<std::is_unsigned<T>::value, void>::type> {
 public:
  static void serialize(const T& num, OutputBuffer& ob) {
    if (num == 0) {
      ob.write_char(0);
      return;
    }

    T num_copy = num;

    while (num_copy > 0) {
      char chunk = num_copy & FILTER_127;
      num_copy >>= 7;
      if (num_copy > 0) {
        chunk |= FILTER_SIGN;
      }
      ob.write_char(chunk);
    }
  }

  static void parse(T& num, InputBuffer& ib) {
    num = 0;
    size_t n_shifts = 0;
    char ch;
    do {
      ch = ib.read_char();
      num |= (ch & FILTER_127) << n_shifts;
      n_shifts += 7;
    } while ((ch & FILTER_SIGN) != 0);
  }

 private:
  constexpr static char FILTER_127 = 0x7f;

  constexpr static char FILTER_SIGN = 0x80;
};

}  // namespace hps

#endif
