#ifndef HPS_UINT_SERIALIZER_H_
#define HPS_UINT_SERIALIZER_H_

#include <cassert>
#include <iostream>
#include <type_traits>

namespace hps {

// Serialize and parse unsigned integer types with base 127 encoding.

template <class T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type serialize(
    const T& num, std::ostream& stream) {
  const int buf_size = sizeof(num) + 2;
  char buf[buf_size];

  if (num == 0) {
    buf[0] = 0;
    stream.write(buf, 1);
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
  stream.write(buf, pos);
}

template <class T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type parse(
    T* num_ptr, std::istream& stream) {
  if (num_ptr == nullptr) num_ptr = new T();
  auto& num = *num_ptr;
  num = 0;
  const int buf_size = sizeof(num) + 2;
  char buf[buf_size];
  int pos = 0;
  stream.read(buf, sizeof(num) + 2);
  while (pos < buf_size) {
    num |= (buf[pos] & 0x7fu) << (7 * pos);
    if ((buf[pos] & 0x80u) == 0) break;
    pos++;
  }
}

}  // namespace hps

#endif
