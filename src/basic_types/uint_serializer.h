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
    const int buf_size = sizeof(num) + 2;
    char buf[buf_size];

    if (num == 0) {
      buf[0] = 0;
      ob.write(buf, 1);
      return;
    }

    int pos = 0;
    T num_copy = num;
    while (pos < buf_size && num_copy > 0) {
      buf[pos] = num_copy & 0x7fu;
      num_copy >>= 7;
      if (num_copy > 0) {
        buf[pos] |= 0x80u;
      }
      pos++;
    }
    assert(num_copy == 0);
    ob.write(buf, pos);
  }

  static void parse(T& num, InputBuffer& ib) {
    num = 0;
    const int buf_size = sizeof(num) + 2;
    char buf[buf_size];
    int pos = 0;
    // std::streampos stream_pos = ib.tellg();
    ib.read(buf, buf_size);
    while (pos < buf_size) {
      T chunk = buf[pos] & 0x7fu;
      num |= chunk << (7 * pos);
      if ((buf[pos] & 0x80u) == 0) break;
      pos++;
    }
    // stream_pos += pos + 1;

    // if (ib.fail()) ib.clear();

    ib.back(buf_size - pos - 1);
  }
};

}  // namespace hps

#endif
