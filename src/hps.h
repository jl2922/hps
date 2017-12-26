#ifndef HPS_H_
#define HPS_H_

#include <iostream>
#include <sstream>
#include "basic_types/basic_types.h"
#include "containers/containers.h"
#include "serializer.h"

namespace hps {
template <class T>
void serialize_to_stream(const T& t, std::ostream& stream) {
  OutputBuffer<Stream> ob(stream);
  Serializer<T, Stream>::serialize(t, ob);
  ob.flush();
}

template <class T>
void parse_from_stream(T& t, std::istream& stream) {
  InputBuffer<Stream> ib(stream);
  Serializer<T, Stream>::parse(t, ib);
}

template <class T>
T parse_from_stream(std::istream& stream) {
  T t;
  parse_from_stream<T>(t, stream);
  return t;
}

template <class T>
void serialize_to_string(const T& t, std::string& str) {
  OutputBuffer<std::string> ob(str);
  Serializer<T, std::string>::serialize(t, ob);
  ob.flush();
}

template <class T>
std::string serialize_to_string(const T& t) {
  std::string str;
  serialize_to_string(t, str);
  return str;
}

template <class T>
void parse_from_string(T& t, const std::string& str) {
  InputBuffer<std::string> ib(str);
  Serializer<T, std::string>::parse(t, ib);
}

template <class T>
T parse_from_string(const std::string& str) {
  T t;
  parse_from_string<T>(t, str);
  return t;
}

}  // namespace hps

#endif
