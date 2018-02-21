#pragma once

#include <iostream>
#include <sstream>
#include "basic_type/basic_type.h"
#include "container/container.h"
#include "serializer.h"

namespace hps {

// Serialize data t to an STL ostream.
template <class T>
void serialize_to_stream(const T& t, std::ostream& stream) {
  OutputBuffer<Stream> ob(stream);
  Serializer<T, Stream>::serialize(t, ob);
  ob.flush();
}

// Parse from an STL istream and save to the data t passed in.
// Recommended for repeated use inside a loop.
template <class T>
void parse_from_stream(T& t, std::istream& stream) {
  InputBuffer<Stream> ib(stream);
  Serializer<T, Stream>::parse(t, ib);
}

// Parse from an STL istream and return the data.
template <class T>
T parse_from_stream(std::istream& stream) {
  T t;
  parse_from_stream<T>(t, stream);
  return t;
}

// Serialize data t to the STL string passed in.
// Recommended for repeated use inside a loop.
template <class T>
void serialize_to_string(const T& t, std::string& str) {
  OutputBuffer<std::string> ob(str);
  Serializer<T, std::string>::serialize(t, ob);
  ob.flush();
}

// Serialize data t to an STL string and return it.
template <class T>
std::string serialize_to_string(const T& t) {
  std::string str;
  serialize_to_string(t, str);
  return str;
}

// Parse from an STL string and save to the data t passed in.
// Recommended for repeated use inside a loop.
template <class T>
void parse_from_string(T& t, const std::string& str) {
  InputBuffer<std::string> ib(str);
  Serializer<T, std::string>::parse(t, ib);
}

// Parse from an STL string and return the data.
template <class T>
T parse_from_string(const std::string& str) {
  T t;
  parse_from_string<T>(t, str);
  return t;
}

// Parse from a char array and save to the data t passed in.
// Recommended for repeated use inside a loop.
template <class T>
void parse_from_char_array(T& t, const char* arr) {
  InputBuffer<char*> ib(arr);
  Serializer<T, char*>::parse(t, ib);
}

// Parse from a char array and return the data.
template <class T>
T parse_from_char_array(const char* arr) {
  T t;
  parse_from_char_array<T>(t, arr);
  return t;
}

}  // namespace hps
