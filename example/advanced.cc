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
