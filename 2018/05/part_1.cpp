#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};
  std::stack<char> polymer{};
  char agent{'\0'};
  while (infile >> agent) {
    if (polymer.empty()) // Nothing to react with
    {
      polymer.push(agent);
      continue;
    }

    if ((tolower(polymer.top()) == tolower(agent)) &&
        ((isupper(polymer.top()) && islower(agent)) ||
         (islower(polymer.top()) && isupper(agent)))) {
      polymer.pop();
    } else {
      polymer.push(agent);
    }
  }

  std::stringstream polymer_string{};
  while (!polymer.empty()) {
    polymer_string << polymer.top();
    polymer.pop();
  }

  std::cout << polymer_string.str().length() << std::endl;

  return 0;
}
