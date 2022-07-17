#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::map<std::pair<int, int>, std::vector<std::string>> square_counts{};
  std::map<std::string, int> id_dimensions{};

  std::string line{};
  std::vector<std::string> tokens{};
  while (std::getline(infile, line)) {
    boost::split(tokens, line, boost::is_any_of(" "), boost::token_compress_on);

    // Starting indices
    auto comma_index = tokens[2].find(',');
    auto colon_index = tokens[2].find(':');
    int x_start = std::stoi(tokens[2].substr(0, comma_index));
    int y_start =
        std::stoi(tokens[2].substr(comma_index + 1, colon_index - comma_index));

    // Dimensions
    auto cross_index = tokens[3].find('x');
    int x_distance = std::stoi(tokens[3].substr(0, cross_index));
    int y_distance = std::stoi(tokens[3].substr(cross_index + 1));

    id_dimensions[tokens[0]] = x_distance * y_distance;

    // Build the map of points to ids which inhabit them
    for (int i = 0; i < x_distance; ++i) {
      for (int j = 0; j < y_distance; ++j) {
        std::pair<int, int> current_point{x_start + i, y_start + j};
        if (square_counts.find(current_point) == square_counts.end()) {
          std::vector<std::string> ids{tokens[0]};
          square_counts[current_point] = ids;
        } else {
          square_counts[current_point].push_back(tokens[0]);
        }
      }
    }
  }

  // Find the non-overlapping one
  for (auto iter = square_counts.begin(); iter != square_counts.end();) {
    if ((*iter).second.size() != 1) {
      iter = square_counts.erase(iter);
    } else {
      ++iter;
    }
  }

  // Single square counts
  std::map<std::string, int> single_square_counts{};
  for (const auto &entry : square_counts) {
    if (single_square_counts.find(entry.second[0]) ==
        single_square_counts.end()) {
      single_square_counts[entry.second[0]] = 1;
    } else {
      single_square_counts[entry.second[0]]++;
    }
  }

  for (const auto &entry : single_square_counts) {
    if (id_dimensions[entry.first] == entry.second) {
      std::cout << entry.first << std::endl;
      break;
    }
  }

  return 0;
}
