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
