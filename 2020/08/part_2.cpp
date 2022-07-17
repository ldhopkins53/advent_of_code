#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int parse_operand(const std::string &operand) {
  auto magnitude = std::stoi(operand.substr(1));
  if (operand[0] == '+') {
    return magnitude;
  }
  return -magnitude;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::vector<std::string> program{};
  std::string current_instruction{};
  while (std::getline(infile, current_instruction)) {
    program.push_back(std::move(current_instruction));
  }

  program[344] = std::string{"nop +0"};
  unsigned line_pointer{0};
  unsigned previous_line_pointer{0};
  int accumulator{0};
  std::set<unsigned> previous_instructions;
  while (true) {
    if (previous_instructions.find(line_pointer) !=
        previous_instructions.end()) {
      std::cout << previous_line_pointer << std::endl;
      std::cout << program[previous_line_pointer] << std::endl;
      break;
    }
    previous_instructions.insert(line_pointer);

    current_instruction = program[line_pointer];
    auto space = current_instruction.find(' ');
    std::string instruction = current_instruction.substr(0, space);
    std::string operand = current_instruction.substr(space + 1);

    previous_line_pointer = line_pointer;
    if (instruction == "nop") {
      line_pointer++;
    } else if (instruction == "acc") {
      accumulator += parse_operand(operand);
      line_pointer++;
    } else {
      line_pointer += parse_operand(operand);
    }
  }
  std::cout << "The answer is: " << accumulator << std::endl;
  return 0;
}
