#ifndef HPS_SERIALIZER_H_
#define HPS_SERIALIZER_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include "buffer/buffer.h"

namespace hps {

template <class T, class B, class Enable = void>
class Serializer {
 public:
  static void serialize(const T&, OutputBuffer<B>&) { default_handler(); }

  static void parse(T&, InputBuffer<B>&) { default_handler(); }

 private:
  static void default_handler() {
    const std::string type_name = typeid(T).name();
    throw std::logic_error("Serializer not found for type " + type_name);
  }
};

}  // namespace hps

#endif
