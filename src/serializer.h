#ifndef HPS_SERIALIZER_H_
#define HPS_SERIALIZER_H_

#include "int_serializer.h"
#include "uint_serializer.h"
#include "vector_serialization.h"

namespace hps {

template <class T>
T parse(std::istream& stream) {
  T t;
  parse(t, stream);
  return t;
}

}  // namespace hps

#endif