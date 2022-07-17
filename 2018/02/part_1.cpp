#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  unsigned two_count{0};
  unsigned three_count{0};
  std::string line{};
  while (std::getline(infile, line)) {
    bool two_found{false};
    bool three_found{false};
    std::map<char, unsigned> char_count{};
    for (const auto &i : line) {
      if (char_count.find(i) == char_count.end()) {
        char_count[i] = 1;
      } else {
        char_count[i]++;
      }
    }

    for (const auto &entry : char_count) {
      if (entry.second == 2) {
        two_found = true;
      } else if (entry.second == 3) {
        three_found = true;
      }
    }

    if (two_found)
      two_count++;
    if (three_found)
      three_count++;
  }

  std::cout << two_count * three_count << std::endl;
  return 0;
}