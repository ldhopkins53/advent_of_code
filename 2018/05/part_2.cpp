#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include <boost/algorithm/string.hpp>

std::string react(const std::string &full_polymer) {
  std::istringstream in{full_polymer};
  std::stack<char> polymer_stack{};
  char agent{'\0'};
  while (in >> agent) {
    if (polymer_stack.empty()) {
      polymer_stack.push(agent);
      continue;
    }

    if ((tolower(polymer_stack.top()) == tolower(agent)) &&
        ((isupper(polymer_stack.top()) && islower(agent)) ||
         (islower(polymer_stack.top()) && isupper(agent)))) {
      polymer_stack.pop();
    } else {
      polymer_stack.push(agent);
    }
  }
  std::stringstream final_polymer{};
  while (!polymer_stack.empty()) {
    final_polymer << polymer_stack.top();
    polymer_stack.pop();
  }

  return final_polymer.str();
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};
  std::string line{};
  std::getline(infile, line);
  auto minimum = line.length();
  for (char lower_case = 'a'; lower_case <= 'z'; ++lower_case) {
    std::string current_version = line;
    char upper_case = toupper(lower_case);
    boost::erase_all(current_version, std::string{lower_case});
    boost::erase_all(current_version, std::string{upper_case});
    auto reacted_version = react(current_version);
    minimum = std::min(minimum, reacted_version.length());
  }
  std::cout << minimum << std::endl;

  return 0;
}
