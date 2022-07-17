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

int calculate_average(std::vector<int> &positions) {
  int median_index = positions.size() / 2;
  std::nth_element(positions.begin(), positions.begin() + median_index,
                   positions.end());
  return positions[median_index];
}

unsigned long long calculate_fuel(std::vector<int> &positions) {
  auto average = calculate_average(positions);
  unsigned long long fuel_requirement{0};
  for (const auto i : positions) {
    fuel_requirement += std::abs(average - i);
  }
  return fuel_requirement;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto positions = get_positions(infile);
  auto fuel = calculate_fuel(positions);
  std::cout << fuel << std::endl;

  return 0;
}
