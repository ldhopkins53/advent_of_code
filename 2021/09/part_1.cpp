#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool is_low(const std::vector<std::vector<int>> &grid, int row, int col) {
  if (row - 1 >= 0) {
    if (grid[row][col] > grid[row - 1][col])
      return false;
  }
  if (row + 1 < grid.size()) {
    if (grid[row][col] > grid[row + 1][col])
      return false;
  }
  if (col - 1 >= 0) {
    if (grid[row][col] > grid[row][col - 1])
      return false;
  }
  if (col + 1 < grid[0].size()) {
    if (grid[row][col] > grid[row][col + 1])
      return false;
  }
  return true;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::string line{};
  std::vector<std::vector<int>> grid{};
  while (std::getline(infile, line)) {
    std::vector<int> line_numbers{};
    std::transform(line.begin(), line.end(), std::back_inserter(line_numbers),
                   [](const auto &i) { return i - '0'; });
    grid.push_back(std::move(line_numbers));
  }

  unsigned long long total_score{0};
  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[0].size(); ++col) {
      if (grid[row][col] == 9)
        continue;
      if (is_low(grid, row, col)) {
        total_score += (1 + grid[row][col]);
      }
    }
  }
  std::cout << total_score << std::endl;
  return 0;
}
