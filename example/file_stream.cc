#include <cassert>
#include <fstream>
#include <iostream>
#include "../src/hps.h"

int main() {
  std::vector<int> data({22, 333, -4444});

  std::ofstream out_file("data.log", std::ofstream::binary);
  std::ifstream in_file("data.log", std::ifstream::binary);

  hps::to_stream(data, out_file);
  out_file.close();

  in_file.seekg(0, in_file.end);
  size_t serialized_size = in_file.tellg();
  in_file.seekg(0, in_file.beg);
  auto parsed = hps::from_stream<std::vector<int>>(in_file);

  assert(parsed == data);

  std::cout << "size (B): " << serialized_size << std::endl;
  // size (B): 6

  return 0;
}
// Compile with C++11 or above.
