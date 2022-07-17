#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

struct Node {
  char value;
  std::map<char, Node *> children{};

  Node(char value) : value(value) {}
};

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::string line{};
  std::vector<std::string> pieces{};

  while (std::getline(infile, line)) {
    std::vector<std::string> tokens{};
    boost::split(tokens, line, boost::is_any_of(" "), boost::token_compress_on);
    pieces.push_back(tokens[1] + tokens[7]);
  }
  for (const auto &i : pieces) {
    std::cout << i << std::endl;
  }
  return 0;
}
