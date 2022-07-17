#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  // Load frequency changes
  long long current{0};
  std::vector<long long> frequency_changes{};
  while (infile >> current) {
    frequency_changes.push_back(current);
  }

  // Iterate through frequency changes until a repetition is found
  std::set<long long> previous_frequencies{};
  long long total{0};
  std::size_t index = 0;
  while (true) {
    if (previous_frequencies.find(total) != previous_frequencies.end()) {
      break;
    }
    previous_frequencies.insert(total);
    total += frequency_changes[index];
    index = (index + 1) % frequency_changes.size();
  }
  std::cout << total << std::endl;
  return 0;
}
