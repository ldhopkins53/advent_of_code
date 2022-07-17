#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::map<std::pair<int, int>, unsigned long long> square_counts{};

  std::string line{};
  std::vector<std::string> tokens{};
  while (std::getline(infile, line)) {
    std::cout << line << std::endl;
    boost::split(tokens, line, boost::is_any_of(" "), boost::token_compress_on);

    // Starting indices
    auto comma_index = tokens[2].find(',');
    auto colon_index = tokens[2].find(':');
    int x_start = std::stoi(tokens[2].substr(0, comma_index));
    int y_start =
        std::stoi(tokens[2].substr(comma_index + 1, colon_index - comma_index));
    std::cout << x_start << " " << y_start << std::endl;

    // Dimensions
    auto cross_index = tokens[3].find('x');
    int x_distance = std::stoi(tokens[3].substr(0, cross_index));
    int y_distance = std::stoi(tokens[3].substr(cross_index + 1));
    std::cout << x_distance << " " << y_distance << std::endl;

    for (int i = 0; i < x_distance; ++i) {
      for (int j = 0; j < y_distance; ++j) {
        std::pair<int, int> current_point{x_start + i, y_start + j};
        if (square_counts.find(current_point) == square_counts.end()) {
          square_counts[current_point] = 1;
        } else {
          square_counts[current_point]++;
        }
      }
    }
  }

  unsigned overlap_count{0};
  for (const auto &entry : square_counts) {
    if (entry.second >= 2) {
      overlap_count++;
    }
  }
  std::cout << overlap_count << std::endl;
  return 0;
}
