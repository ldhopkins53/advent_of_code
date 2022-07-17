#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

std::vector<unsigned long long> read_program(std::ifstream &infile) {
  std::string line{};
  std::getline(infile, line);
  std::vector<std::string> split_numbers{};
  boost::split(split_numbers, line, boost::is_any_of(","),
               boost::token_compress_on);
  std::vector<unsigned long long> numbers{};
  std::transform(split_numbers.begin(), split_numbers.end(),
                 std::back_inserter(numbers),
                 [](const auto &i) { return std::stoull(i); });
  return numbers;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto program = read_program(infile);
  program[1] = 12;
  program[2] = 2;

  int program_counter{0};
  bool loop = true;
  while (loop) {
    int op = program[program_counter];
    int destination, operand_one, operand_two;
    switch (op) {
    case 1:
      // handle addition
      operand_one = program[program_counter + 1];
      operand_two = program[program_counter + 2];
      destination = program[program_counter + 3];
      program[destination] = program[operand_one] + program[operand_two];
      break;
    case 2:
      // handle multiplication
      operand_one = program[program_counter + 1];
      operand_two = program[program_counter + 2];
      destination = program[program_counter + 3];
      program[destination] = program[operand_one] * program[operand_two];
      break;
    case 99:
      loop = false;
    }
    program_counter += 4;
  }

  std::cout << program[0] << std::endl;
  return 0;
}
