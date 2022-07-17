#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int calculate_distance(const std::string &line_one,
                       const std::string &line_two) {
  int distance{0};
  for (int i = 0; i < line_one.size(); ++i) {
    if (line_one[i] != line_two[i])
      ++distance;
  }
  return distance;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::vector<std::string> lines{};
  std::string line{};
  while (std::getline(infile, line)) {
    lines.push_back(std::move(line));
  }

  std::string left{}, right{};
  bool found{false};
  for (int i = 0; i < lines.size(); ++i) {
    if (found)
      break;
    for (int j = i + 1; j < lines.size(); ++j) {
      if (calculate_distance(lines[i], lines[j]) == 1) {
        left = lines[i];
        right = lines[j];
        found = true;
        break;
      }
    }
  }

  for (int i = 0; i < left.size(); ++i) {
    if (left[i] == right[i])
      std::cout << left[i];
  }
  std::cout << std::endl;
  return 0;
}