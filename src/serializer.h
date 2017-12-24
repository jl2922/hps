#ifndef HPS_SERIALIZER_H_
#define HPS_SERIALIZER_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace hps {

template <class T, class Enable = void>
class Serializer {
 public:
  static void serialize(const T& t, std::ostream& stream) {
    (void)t;
    (void)stream;
    const std::string type_name = typeid(T).name();
    throw std::logic_error("serialize not implemented for type " + type_name);
  }

  static void parse(T& t, std::istream& stream) {
    (void)t;
    (void)stream;
    const std::string type_name = typeid(T).name();
    throw std::logic_error("parse not implemented for type " + type_name);
  }
};

}  // namespace hps

#endif