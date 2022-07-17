#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

unsigned do_partition(const std::string &entries, char upper_indicator,
                      char lower_indicator) {
  unsigned high_end = (1 << entries.length()) - 1;
  unsigned lower = 0, upper = high_end;
  for (auto i = 0; i < entries.length(); ++i) {
    unsigned mid = (upper + lower + 1) / 2;
    if (entries[i] == upper_indicator) {
      upper = mid - 1;
    } else {
      lower = mid;
    }
  }
  assert(lower == upper);
  return lower;
}

unsigned calculate_id(const std::string &line) {
  unsigned row = do_partition(line.substr(0, 7), 'F', 'B');
  unsigned column = do_partition(line.substr(7), 'L', 'R');
  return (row * 8) + column;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};
  std::string line;
  unsigned current_max{0};
  while (std::getline(infile, line)) {
    auto i = calculate_id(line);
    current_max = std::max(i, current_max);
  }
  std::cout << "The highest seat ID is: " << current_max << std::endl;
  return 0;
}
