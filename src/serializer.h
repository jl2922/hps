#ifndef HPS_SERIALIZER_H_
#define HPS_SERIALIZER_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include "input_buffer.h"
#include "output_buffer.h"

namespace hps {

template <class T, class Enable = void>
class Serializer {
 public:
  static void serialize(const T& t, OutputBuffer& ob) {
    (void)t;  // Avoid warnings.
    (void)ob;
    default_handler();
  }

  static void parse(T& t, InputBuffer& ib) {
    (void)t;
    (void)ib;
    default_handler();
  }

 private:
  static void default_handler() {
    const std::string type_name = typeid(T).name();
    throw std::logic_error("Serializer not found for type " + type_name);
  }
};

}  // namespace hps

#endif