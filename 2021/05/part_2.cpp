#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

std::pair<int, int> split_range(const std::string &range) {
  std::vector<std::string> boundaries{};
  boost::split(boundaries, range, boost::is_any_of(","),
               boost::token_compress_on);
  return {std::stoi(boundaries[0]), std::stoi(boundaries[1])};
}

std::pair<std::pair<int, int>, std::pair<int, int>>
split_line(const std::string &current_line) {
  std::vector<std::string> tokens{};
  boost::split(tokens, current_line, boost::is_any_of(" "),
               boost::token_compress_on);
  std::string first_range{tokens[0]}, second_range{tokens[2]};
  return {split_range(first_range), split_range(second_range)};
}

unsigned count_intersections(const std::map<std::pair<int, int>, int> &grid) {
  unsigned count{0};
  for (const auto &point : grid) {
    if (point.second > 1) {
      ++count;
    }
  }
  return count;
}

void process_line(std::map<std::pair<int, int>, int> &grid,
                  const std::string &current_line) {
  auto [first_range, second_range] = split_line(current_line);

  if (first_range.first != second_range.first &&
      first_range.second != second_range.second) {
    // Diagonal lines
    int row_sign = first_range.first < second_range.first ? 1 : -1;
    int col_sign = first_range.second < second_range.second ? 1 : -1;
    std::cout << first_range.first << " " << first_range.second << std::endl;
    std::cout << second_range.first << " " << second_range.second << std::endl;
    for (int i = 0;
         i < (second_range.second - first_range.second) * col_sign + 1; ++i) {
      const std::pair<int, int> current_spot = {
          first_range.first + (i * row_sign),
          first_range.second + (i * col_sign)};
      std::cout << current_spot.first << " " << current_spot.second
                << std::endl;
      if (grid.find(current_spot) == grid.end()) {
        grid[current_spot] = 1;
      } else {
        grid[current_spot] = grid[current_spot] + 1;
      }
    }
  } else if (first_range.first == second_range.first) {
    // Working equal rows
    for (int i = std::min(first_range.second, second_range.second);
         i <= std::max(first_range.second, second_range.second); ++i) {
      if (grid.find({first_range.first, i}) == grid.end()) {
        grid[{first_range.first, i}] = 1;
      } else {
        grid[{first_range.first, i}] = grid[{first_range.first, i}] + 1;
      }
    }
  } else {
    // Working equal columns
    for (int i = std::min(first_range.first, second_range.first);
         i <= std::max(first_range.first, second_range.first); ++i) {
      if (grid.find({i, first_range.second}) == grid.end()) {
        grid[{i, first_range.second}] = 1;
      } else {

        grid[{i, first_range.second}] = grid[{i, first_range.second}] + 1;
      }
    }
  }
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  // Create starting grid
  std::map<std::pair<int, int>, int> grid{};

  // Work through each line
  std::string current_line{""};
  while (infile) {
    std::getline(infile, current_line);
    if (current_line == "") {
      break;
    }
    process_line(grid, current_line);
  }
  auto count = count_intersections(grid);
  std::cout << "The answer is: " << count << std::endl;
  return 0;
}
