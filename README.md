# HPS

A C++11 High Performance Serialization Library.

[![Build Status](https://travis-ci.org/jl2922/hps.svg?branch=master&style=flat)](https://travis-ci.org/jl2922/hps)

## Overview

HPS is a high performance header-only C++11 library for data serialization.
It is designed for high performance computing where we need to efficiently serialize highly structured data or objects to a sufficiently small and flat structure and pass them over the network, write them to the file system, or simply to compress them to reduce the memory consumption.

It has the **state of the art performance** regarding both the speed and the size of the serialized messages.
Check the benchmarks below.

In addition, it requires the least amount of human efforts to use for common data structures in high performance computing, such as arrays, matrices, maps, etc.
There is **no need for separate schema files or special data structures**, HPS works with STL containers and user-defined types directly, just like Boost but much faster.
This design makes the binding of data and their methods more natural and cohesive and gives better performance / data encapsulation on generic libraries and static polymorphism classes.

Note: HPS requires manual handling of data backward compatibility issues.

## Installation

HPS is a header-only library.
Simply include the `hps.h` file, which includes all the other headers.

## Usage

HPS is super easy to use.
For primitive types and most STL containers, serialization requires only one line of code.

```c++
#include <cassert>
#include <iostream>
#include "../src/hps.h"

int main() {
  std::vector<int> data({22, 333, -4444});

  std::string serialized = hps::to_string(data);
  auto parsed = hps::from_string<std::vector<int>>(serialized);

  assert(parsed == data);

  std::cout << "size (B): " << serialized.size() << std::endl;
  // size (B): 6

  return 0;
}
// Compile with C++11 or above.
```
Then we can send the string over the network in MPI for example
```c++
MPI_Send(serialized.c_str(), serialized.size(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
```
There are also the `to_stream` and `from_stream` functions for writing the data to or reading it from file streams.
For example
```c++
std::ofstream out_file("data.log", std::ofstream::binary);
hps::to_stream(data, out_file);
std::ifstream in_file("data.log", std::ifstream::binary);
auto parsed = hps::from_stream<std::vector<int>>(in_file);
```
The bottom of this document contains all the APIs that HPS provides.

We can also extend HPS to support custom types.
HPS internally uses static polymorphism on the class `Serializer<DataType, BufferType>` to support different types.
`Serializer<DataType, BufferType>` will call the `serialize` and `parse` method of the corresponding type by default.
All we need to do is provide the `serialize` and `parse` method or specialize the `Serializer` for the new type, and HPS will support it, together with any combination of this type with STL containers and other specialized types.
We recommend providing the `serialize` and `parse` method whenever you have control over the structure of the new type.

The following example shows the serialization of a typical quantum system object consisting of several electrons, some of which are excited from orbitals `orbs_from` to `orbs_to`.

```c++
#include <cassert>
#include <iostream>
#include "../src/hps.h"

class QuantumState {
 public:
  unsigned n_elecs;
  std::unordered_set<unsigned> orbs_from;
  std::unordered_set<unsigned> orbs_to;

  template <class B>
  void serialize(B& buf) const {
    buf << n_elecs << orbs_from << orbs_to;
  }

  template <class B>
  void parse(B& buf) {
    buf >> n_elecs >> orbs_from >> orbs_to;
  }
};

int main() {
  QuantumState qs;

  qs.n_elecs = 33;
  qs.orbs_from.insert({11, 22});
  qs.orbs_to.insert({44, 66});

  std::string serialized = hps::to_string(qs);

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

The major difference between protobuf's encoding scheme and HPS' is that the **field numbers or wire types are not stored** and the messages are always serialized and parsed in the same order unless explicitly specialized for custom types.
This gives HPS a significant advantage in both the speed and the size of the serialized messages over protobuf on data with nested structures, especially when deeper structures are small.

Another difference is in the handling of the integral types.
There are no specific types for signed integers like the `sint32` or `sint64` in protobuf and the **zigzag varint encoding will be used on standard int types**, i.e. `int`, `long long`, etc.
And before serialization, we can use smaller integral types such as `int16_t` to store the data more compactly in memory constrained environments, instead of at least `int32` as in protobuf.

## Benchmark

The performance of HPS comparing to other well-known C++ serializers for some most common data structures in high performance computing are as follows:

Note:
The sparse matrix is stored as a list of rows, each of which contains a list of 64-bit integers for the column indices and a list of doubles for the values.
The hash map is a map from strings to doubles.
Both HPS and Boost can serialize `std::unordered_map` directly, ProtoBuf uses its own Map type which may not be a hash map, and CapnProto does not support hash map or similar types at this time.
The test codes are in the [benchmark](https://github.com/jl2922/hps/tree/master/src/benchmark) directory.

![Serialize and Parse Time](https://raw.githubusercontent.com/jl2922/hps/master/src/benchmark/time.png)

![Serialized Message Size](https://raw.githubusercontent.com/jl2922/hps/master/src/benchmark/size.png)

In addition to the traditional benchmarks for computational cost, we also provide the human efforts cost in terms of source lines of code for these test cases:

| SLOC | double array | sparse matrix | hash map | fixed cost |
| --- | :---: | :---: | :---: | :---: |
| **protobuf** | 12 | 23 | 12 | 17 |
| **capnproto** | 15 | 25 | - | 21 |
| **boost** | 13 | 20 | 13 | 13 |
| **hps** | 7 | 16 | 7 | 2 |

Note: fixed cost includes the estimated amount of lines of commands needed for a proficient user to install the library, set the environment variables, extra lines of code needed in the Makefile, and various includes, etc.

## API Reference

```c++
// Serialize data t to an STL ostream.
void to_stream(const T& t, std::ostream& stream);
```
```c++
// Parse from an STL istream and save to the data t passed in.
// Recommended for repeated use inside a loop.
void from_stream(T& t, std::istream& stream);
```
```c++
// Parse from an STL istream and return the data.
T from_stream<T>(std::istream& stream);
```
```c++
// Serialize data t to the STL string passed in.
// Recommended for repeated use inside a loop.
void to_string(const T& t, std::string& str);
```
```c++
// Serialize data t to an STL string and return it.
std::string to_string(const T& t);
```
```c++
// Parse from an STL string and save to the data t passed in.
// Recommended for repeated use inside a loop.
void from_string(T& t, const std::string& str);
```
```c++
// Parse from an STL string and return the data.
T from_string<T>(const std::string& str);
```
```c++
// Parse from a char array and save to the data t passed in.
// Recommended for repeated use inside a loop.
void from_char_array(T& t, const char* arr);
```
```c++
// Parse from a char array and return the data.
T from_char_array<T>(const char* arr);
```

HPS supports the following types and any combinations of them out of the box:

* All primitive numeric types, a.k.a. `std::is_arithmetic<T>`, e.g. `int, double, bool, char, uint8_t, size_t, ...`
* STL containers `string, array, deque, list, map, unordered_map, set, unordered_set, pair, vector, unique_ptr`.

## Tips for Heterogeneous Data

Heterogeneous data here refer messages that contain data structures that occur repeatedly and have some fields in them missing irregularly in different instances of the structure.

There is no panacea for achieving the best performance for this type of data in all cases.

Protobuf uses an additional integer to indicate the existence of each field, which is best suitable for cases where there are lots of fields and most of them are missing.

Another possible encoding scheme is bit representation, i.e., use a bit vector to indicate the existence of the fields.
This is best suitable for cases where there are not many fields and fields are missing less often.
There is no need to deal with bit operations directly.
An STL `vector<bool>` will use a compact format automatically, i.e., eight booleans in a byte, and same for the HPS serialized version.

And for cases where most of the fields seldom have missing values, the reverse of protobuf's scheme may be the best choice, i.e., use a vector to store the indices of the missing fields.
