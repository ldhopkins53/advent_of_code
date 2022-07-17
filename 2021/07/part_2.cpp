#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

std::vector<int> get_positions(std::ifstream &infile) {
  std::string number_line{};
  std::getline(infile, number_line);
  std::vector<std::string> numbers{};
  boost::split(numbers, number_line, boost::is_any_of(","),
               boost::token_compress_on);
  std::vector<int> positions{};
  std::transform(numbers.begin(), numbers.end(), std::back_inserter(positions),
                 [](const std::string &i) { return std::stoi(i); });
  return positions;
}

unsigned long long calculate_fuel(std::vector<int> &positions, int target) {
  unsigned long long fuel_requirement{0};
  for (const auto i : positions) {
    for (int j = 1; j <= std::abs(target - i); ++j) {
      fuel_requirement += j;
    }
  }
  return fuel_requirement;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto positions = get_positions(infile);
  auto min_fuel = calculate_fuel(positions, 0);
  for (int i = 1; i < *std::max_element(positions.begin(), positions.end());
       ++i) {
    auto fuel = calculate_fuel(positions, i);
    min_fuel = std::min(fuel, min_fuel);
  }
  std::cout << min_fuel << std::endl;

  return 0;
}
