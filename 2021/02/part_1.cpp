#include <fstream>
#include <iostream>
#include <map>
#include <string>

enum class Direction { FORWARD, DOWN, UP };
static std::map<std::string, Direction> direction_mapping{
    {"forward", Direction::FORWARD},
    {"up", Direction::UP},
    {"down", Direction::DOWN}};

int main(int argc, char **argv) {
  std::string input_file = argv[1];
  std::ifstream infile(input_file);

  unsigned horizontal{0};
  unsigned depth{0};

  std::string instruction;
  int magnitude;
  while (infile >> instruction >> magnitude) {
    switch (direction_mapping[instruction]) {
    case Direction::FORWARD:
      horizontal += magnitude;
      break;
    case Direction::UP:
      depth -= magnitude;
      break;
    case Direction::DOWN:
      depth += magnitude;
      break;
    }
  }
  std::cout << "Horizontal: " << horizontal << std::endl;
  std::cout << "Depth: " << depth << std::endl;
  std::cout << "Answer: " << depth * horizontal << std::endl;
}
