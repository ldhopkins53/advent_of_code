#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

void display_grid(const std::vector<std::vector<int>> &grid) {
  for (const auto &line : grid) {
    for (const auto &entry : line) {
      std::cout << entry << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<int>> read_grid(std::ifstream &infile) {
  std::vector<std::vector<int>> grid{};
  std::string line{};
  while (std::getline(infile, line)) {
    std::vector<int> numbers{};
    std::transform(line.begin(), line.end(), std::back_inserter(numbers),
                   [](auto i) { return i - '0'; });
    grid.push_back(std::move(numbers));
  }
  return grid;
}

void increment_all(std::vector<std::vector<int>> &grid) {
  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[0].size(); ++col) {
      grid[row][col] += 1;
    }
  }
}

void increment_adjacent(std::vector<std::vector<int>> &grid, int row, int col) {
  for (int row_mod = -1; row_mod <= 1; ++row_mod) {
    for (int col_mod = -1; col_mod <= 1; ++col_mod) {
      if (row_mod == 0 && col_mod == 0)
        continue;

      auto new_row = row + row_mod;
      auto new_col = col + col_mod;
      if (new_row < 0 || new_row >= grid.size())
        continue;
      if (new_col < 0 || new_col >= grid[0].size())
        continue;
      grid[new_row][new_col]++;
    }
  }
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};
  auto grid = read_grid(infile);

  display_grid(grid);

  unsigned long long flashes{0};
  for (int step = 0; step < std::stoi(argv[2]); ++step) {
    std::cout << std::endl;
    std::set<std::pair<int, int>> flashed_this_step{};
    increment_all(grid);
    while (true) {
      bool flashed = false;
      for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
          if (grid[row][col] > 9 &&
              flashed_this_step.find({row, col}) == flashed_this_step.end()) {
            std::cout << row << " " << col << " flashed" << std::endl;
            flashed_this_step.insert({row, col});
            flashes++;
            flashed = true;
          }
        }
      }
      for (const auto &entry : flashed_this_step) {
        increment_adjacent(grid, entry.first, entry.second);
      }
      if (!flashed) {
        // Nothing flashed so we're done with this step
        break;
      }
    }
    for (const auto &flashed : flashed_this_step) {
      grid[flashed.first][flashed.second] = 0;
    }
    display_grid(grid);
  }
  return 0;
}
