#include <cassert>
#include <iostream>
#include <unordered_set>
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
