#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::vector<unsigned> group_counts{};
  while (infile) // Keep reading until we run out of entries
  {
    std::string current_group{};
    std::string current_line{};
    do { // Read each group delimited by a blank line
      std::getline(infile, current_line);
      current_group += current_line;
    } while (current_line != "");
    std::set<char> unique_characters{current_group.cbegin(),
                                     current_group.cend()};
    group_counts.push_back(unique_characters.size());
  }

  auto sum_of_elems =
      std::accumulate(group_counts.cbegin(), group_counts.cend(), 0);
  std::cout << "The answer is: " << sum_of_elems << std::endl;
  return 0;
}
