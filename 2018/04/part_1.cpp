#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::vector<std::string> lines{};
  std::string line{};
  while (std::getline(infile, line)) {
    lines.push_back(std::move(line));
  }
  std::sort(lines.begin(), lines.end());

  for (const auto &i : lines) {
    std::cout << i << std::endl;
  }

  return 0;
}
