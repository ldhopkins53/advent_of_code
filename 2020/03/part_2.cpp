#include <fstream>
#include <iostream>
#include <string>
#include <vector>

unsigned long long find_hit_trees(const std::vector<std::string> &lines,
                                  int row_increment, int column_increment) {
  auto col_length = lines[0].length();
  auto row{row_increment};
  auto col{column_increment};
  unsigned long long tree_count{0};
  while (row < lines.size()) {
    if (lines[row][col] == '#') {
      ++tree_count;
    }
    col = (col + column_increment) % col_length;
    row += row_increment;
  }
  return tree_count;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile(filename);

  std::vector<std::string> lines{};
  std::string line{};
  while (infile >> line) {
    lines.push_back(std::move(line));
  }

  const std::vector<std::pair<int, int>> variations = {
      {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  unsigned long long total = 1;
  for (const auto [col, row] : variations) {
    total *= find_hit_trees(lines, row, col);
  }

  std::cout << "The answer is: " << total << std::endl;
  return 0;
}
