#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>

static const std::map<char, char> delimiter_mapping{
    {')', '('}, {'>', '<'}, {']', '['}, {'}', '{'}};
static const std::map<char, int> error_value{
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::string line{};
  std::stack<char> s{};
  long long error_score{0};
  while (std::getline(infile, line)) {
    for (const char c : line) {
      if (delimiter_mapping.find(c) == delimiter_mapping.end()) {
        // Opening character
        s.push(c);
        continue;
      }
      // Found a closing character
      if (s.top() != delimiter_mapping.at(c)) {
        std::cout << c << std::endl;
        error_score += error_value.at(c);
        break;
      }
      s.pop();
    }
  }
  std::cout << error_score << std::endl;
  return 0;
}
