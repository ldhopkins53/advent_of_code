#include <algorithm>
#include <fstream>
#include <iostream>
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

std::set<std::pair<long long, long long>>
build_wire_points(const std::vector<std::string> &wire_directions) {
  std::set<std::pair<long long, long long>> wire_points{};
  long long x = 0;
  long long y = 0;
  for (const auto &direction : wire_directions) {
    auto direction_magnitude = std::stoi(direction.substr(1)) - 1;
    switch (direction[0]) {
    case 'U':
      // handle going up
      for (int i = 0; i < direction_magnitude; ++i) {
        y += 1;
        wire_points.insert({x, y});
      }
      break;
    case 'D':
      // handle going down
      for (int i = 0; i < direction_magnitude; ++i) {
        y -= 1;
        wire_points.insert({x, y});
      }
      break;
    case 'L':
      // handle going left
      for (int i = 0; i < direction_magnitude; ++i) {
        x -= 1;
        wire_points.insert({x, y});
      }
      break;
    case 'R':
      // handle going right
      for (int i = 0; i < direction_magnitude; ++i) {
        x += 1;
        wire_points.insert({x, y});
      }
      break;
    }
  }
  return wire_points;
}

long long calculate_distance(const std::pair<long long, long long> &point) {
  return std::abs(point.first) + std::abs(point.second);
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto first_wire = read_wire(infile);
  auto second_wire = read_wire(infile);

  auto first_wire_points = build_wire_points(first_wire);
  auto second_wire_points = build_wire_points(second_wire);

  std::vector<std::pair<long long, long long>> intersecting_points{};
  std::set_intersection(first_wire_points.begin(), first_wire_points.end(),
                        second_wire_points.begin(), second_wire_points.end(),
                        std::back_inserter(intersecting_points));

  auto min_distance = calculate_distance(intersecting_points[0]);
  for (const auto &point : intersecting_points) {
    min_distance = std::min(min_distance, calculate_distance(point));
  }
  std::cout << min_distance << std::endl;

  return 0;
}
