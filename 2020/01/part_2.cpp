#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::string filename(argv[1]);
  std::ifstream infile(filename);

  std::vector<int> values{};
  int value{0};
  while (infile >> value) {
    values.push_back(value);
  }

  for (const auto i : values) {
    for (const auto j : values) {
      for (const auto k : values) {
        auto sum = i + j + k;
        if (i + j + k == 2020) {
          std::cout << "The answer is: " << i * j * k << std::endl;
          return 0;
        }
      }
    }
  }
  return 1;
}
