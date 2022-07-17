#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  std::vector<unsigned> seat_ids{};
  while (std::getline(infile, line)) {
    auto i = calculate_id(line);
    seat_ids.push_back(i);
  }
  std::sort(seat_ids.begin(), seat_ids.end());

  for (auto i = 1; i < seat_ids.size(); ++i) {
    auto current_id = seat_ids[i];
    if ((seat_ids[i - 1] == current_id - 1) &&
        (seat_ids[i + 1] == current_id + 1)) {
      continue;
    }
    std::cout << "The answer is " << current_id + 1 << std::endl;
    break;
  }
  return 0;
}
