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

  auto total = find_hit_trees(lines, 1, 3);
  std::cout << "You hit " << total << " trees" << std::endl;
  return 0;
}
