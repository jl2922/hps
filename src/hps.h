#include <iostream>
#include <sstream>
#include "basic_types/float_serializer.h"
#include "basic_types/int_serializer.h"
#include "basic_types/string_serializer.h"
#include "basic_types/uint_serializer.h"
#include "containers/array_serializer.h"
#include "containers/deque_serializer.h"
#include "containers/list_serializer.h"
#include "containers/map_serializer.h"
#include "containers/pair_serializer.h"
#include "containers/set_serializer.h"
#include "containers/unordered_map_serializer.h"
#include "containers/unordered_set_serializer.h"
#include "containers/vector_serializer.h"
#include "serializer.h"

namespace hps {
template <class T>
void serialize(const T& t, std::ostream& stream) {
  Serializer<T>::serialize(t, stream);
}

template <class T>
void parse(T& t, std::istream& stream) {
  Serializer<T>::parse(t, stream);
}

template <class T>
T parse(std::istream& stream) {
  T t;
  parse<T>(t, stream);
  return t;
}

template <class T>
void serialize_to_string(const T& t, std::string& str) {
  std::stringstream ss;
  serialize(t, ss);
  str = ss.str();
}

template <class T>
std::string serialize_to_string(const T& t) {
  std::string str;
  serialize_to_string(t, str);
  return str;
}

template <class T>
void parse_from_string(T& t, const std::string& str) {
  std::stringstream ss(str);
  parse(t, ss);
}

template <class T>
T parse_from_string(const std::string& str) {
  T t;
  parse_from_string<T>(t, str);
  return t;
}

}  // namespace hps