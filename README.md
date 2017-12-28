# HPS

A C++11 Serializer for High Performance Computing.

[![Build Status](https://travis-ci.org/jl2922/hps.svg?branch=master&style=flat)](https://travis-ci.org/jl2922/hps)

## Overview

HPS is a header-only C++11 serialization library for high performance computing where we need to efficiently serialize and pass highly structured data over the network, write them to the file system, or compress them to reduce the memory consumption.

It is designed to be extremely easy to program and ultrafast for serializing common data structures in high performance computing, but may require some human efforts for heterogeneous data and backward data compatibility issues, which seldom occurs in scientific computing.

## Installation

HPS is a header-only library.
Simply include the `hps.h` file, which will include all the other headers.

## Usage

HPS is super easy to use.
For primitive types and most STL containers, serialization requires only one line of code.

```c++
#include <cassert>
#include <iostream>
#include "../src/hps.h"

int main() {
  std::vector<int> data({22, 333, -4444});

  std::string serialized = hps::serialize_to_string(data);
  auto parsed = hps::parse_from_string<std::vector<int>>(serialized);

  assert(parsed == data);

  std::cout << "size (B): " << serialized.size() << std::endl;
  // size (B): 6

  return 0;
}
// Compile with C++11 or above.
```

We can also extend HPS to support custom types.
HPS internally uses static polymorphism on class `Serializer<DataType, BufferType>` to support different types.
All we need to do is to specialize the `Serializer` for the new type and HPS will support it and also support any combination of this type with STL containers and other specialized types.

The following example shows the serialization of a typical quantum system consisting of some electrons, a few of which are excited from orbital `orbs_from` to `orbs_to`.

```c++
#include <cassert>
#include <iostream>
#include "../src/hps.h"

class QuantumState {
 public:
  uint16_t n_elecs;
  std::unordered_set<uint16_t> orbs_from;
  std::unordered_set<uint16_t> orbs_to;
};

namespace hps {
template <class B>
class Serializer<QuantumState, B> {
 public:
  static void serialize(const QuantumState& qs, OutputBuffer<B>& ob) {
    Serializer<uint16_t, B>::serialize(qs.n_elecs, ob);
    Serializer<std::unordered_set<uint16_t>, B>::serialize(qs.orbs_from, ob);
    Serializer<std::unordered_set<uint16_t>, B>::serialize(qs.orbs_to, ob);
  }
  static void parse(QuantumState& qs, InputBuffer<B>& ib) {
    Serializer<uint16_t, B>::parse(qs.n_elecs, ib);
    Serializer<std::unordered_set<uint16_t>, B>::parse(qs.orbs_from, ib);
    Serializer<std::unordered_set<uint16_t>, B>::parse(qs.orbs_to, ib);
  }
};
}  // namespace hps

int main() {
  QuantumState qs;

  qs.n_elecs = 33;
  qs.orbs_from.insert({11, 22});
  qs.orbs_to.insert({44, 66});

  std::string serialized = hps::serialize_to_string(qs);

  std::cout << "size (B): " << serialized.size() << std::endl;
  // size (B): 7

  return 0;
}
// Compile with C++11 or above.
```

If needed, we can also leverage `SFINAE` to support multiple types with the same piece of code.
HPS makes extensive use of that internally.
See [float_serializer.h](https://github.com/jl2922/hps/blob/master/src/basic_type/float_serializer.h) for example.

## Encoding Scheme

The encoding scheme of HPS is very similar to Google's protobuf.
Google provides an [extremely detailed exlanation](https://developers.google.com/protocol-buffers/docs/encoding) on that.

The differences between protobuf's encoding scheme and HPS' are:

* Standard int types (int, long, etc) uses zigzag encoding as well.
* No field numbers or wire types are stored, messages are always serialized and parsed in the same order (Unless explicitly specialized for custom types).

## Benchmark

The performance of HPS comparing to other well-known C++ serializers for some most common data structures in high performance computing are as follows:

Note:
For the hash map benchmarks, both HPS and Boost serialize `std::unordered_map` directly, ProtoBuf uses its own Map type which may not be a hash map, and CapnProto does not support hash map or similar types.
The test codes are in the [benchmark](https://github.com/jl2922/hps/tree/master/src/benchmark) directory.

![Serialize and Parse Time](https://raw.githubusercontent.com/jl2922/hps/master/src/benchmark/time.png)

![Serialized Message Size](https://raw.githubusercontent.com/jl2922/hps/master/src/benchmark/size.png)

## API Reference

```c++
// Serialize data t to an STL ostream.
void serialize_to_stream(const T& t, std::ostream& stream);
```
```c++
// Parse from an STL istream and save to the data t passed in.
void parse_from_stream(T& t, std::istream& stream);
```
```c++
// Parse from an STL istream and return the data.
T parse_from_stream<T>(std::istream& stream);
```
```c++
// Serialize data t to the STL string passed in.
void serialize_to_string(const T& t, std::string& str);
```
```c++
// Serialize data t to an STL string and return it.
std::string serialize_to_string(const T& t);
```
```c++
// Parse from an STL string and save to the data t passed in.
void parse_from_string(T& t, const std::string& str);
```
```c++
// Parse from an STL string and return the data.
T parse_from_string<T>(const std::string& str);
```

HPS supports the following types and any combinations of them out of the box:

* All primitive numeric types, e.g. `int, double, bool, char, uint8_t, size_t, ...`
* `string, array, deque, list, map, unordered_map, set, unordered_set, pair, vector`
