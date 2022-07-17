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

unsigned count_intersections(const std::vector<int *> &grid) {
  unsigned count{0};
  for (const auto &line : grid) {
    for (int i = 0; i < 1000; ++i) {
      if (line[i] > 1) {
        ++count;
      }
    }
  }
  return count;
}

void process_line(std::vector<int *> &grid, const std::string &current_line) {
  auto [first_range, second_range] = split_line(current_line);

  if (first_range.first != second_range.first &&
      first_range.second != second_range.second) {
    // Ignoring misaligned lines for now
    return;
  } else if (first_range.first == second_range.first) {
    // Working equal rows
    for (int i = std::min(first_range.second, second_range.second);
         i <= std::max(first_range.second, second_range.second); ++i) {
      grid[first_range.first][i] = grid[first_range.first][i] + 1;
    }
  } else {
    // Working equal columns
    for (int i = std::min(first_range.first, second_range.first);
         i <= std::max(first_range.first, second_range.first); ++i) {
      grid[i][first_range.second] = grid[i][first_range.second] + 1;
    }
  }
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  // Create starting grid
  std::vector<int *> grid(1000);
  for (int i = 0; i < 1000; ++i) {
    grid[i] = new int[1000];
    std::fill(grid[i], grid[i] + 1000, 0);
  }

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
