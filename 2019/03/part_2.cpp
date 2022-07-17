#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

std::vector<std::string> read_wire(std::ifstream &infile) {
  std::string line{};
  std::getline(infile, line);
  std::vector<std::string> wire_directions{};
  boost::split(wire_directions, line, boost::is_any_of(","),
               boost::token_compress_on);
  return wire_directions;
}

std::pair<std::map<std::pair<long long, long long>, long long>,
          std::set<std::pair<long long, long long>>>
build_wire_points(const std::vector<std::string> &wire_directions) {
  std::map<std::pair<long long, long long>, long long> step_counts{};
  std::set<std::pair<long long, long long>> wire_points{};
  long long x = 0;
  long long y = 0;
  long long steps = 0;
  for (const auto &direction : wire_directions) {
    auto direction_magnitude = std::stoi(direction.substr(1));
    long long *target_value = nullptr;
    int sign = 1;
    switch (direction[0]) {
    case 'U':
      // handle going up
      target_value = &y;
      sign = 1;
      break;
    case 'D':
      // handle going down
      target_value = &y;
      sign = -1;
      break;
    case 'L':
      // handle going left
      target_value = &x;
      sign = -1;
      break;
    case 'R':
      // handle going right
      target_value = &x;
      sign = 1;
      break;
    }
    for (int i = 0; i < direction_magnitude; ++i) {
      steps++;
      if (step_counts.find({x, y}) == step_counts.end()) {
        step_counts[{x, y}] = steps;
      }
      *target_value = *target_value + sign;
      wire_points.insert({x, y});
    }
  }
  return {step_counts, wire_points};
}

long long calculate_distance(const std::pair<long long, long long> &point) {
  return std::abs(point.first) + std::abs(point.second);
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto first_wire = read_wire(infile);
  auto second_wire = read_wire(infile);

  auto [first_step_counts, first_wire_points] = build_wire_points(first_wire);
  auto [second_step_counts, second_wire_points] =
      build_wire_points(second_wire);

  std::vector<std::pair<long long, long long>> intersecting_points{};
  std::set_intersection(first_wire_points.begin(), first_wire_points.end(),
                        second_wire_points.begin(), second_wire_points.end(),
                        std::back_inserter(intersecting_points));

  auto min_distance = std::numeric_limits<long long>::max();
  for (const auto &point : intersecting_points) {
    long long new_distance =
        first_step_counts.at(point) + second_step_counts.at(point);
    min_distance = std::min(min_distance, new_distance);
  }
  std::cout << min_distance - 2 << std::endl;

  return 0;
}
