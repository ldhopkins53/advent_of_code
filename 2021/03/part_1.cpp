#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  std::string filename(argv[1]);
  std::ifstream infile(filename);

  std::vector<std::string> lines;
  std::string line;
  while (infile >> line) {
    lines.push_back(line);
  }

  std::string gamma_rate_string{};
  for (auto i = 0; i < lines[0].length(); ++i) {
    int zero_count = 0;
    int one_count = 0;
    for (auto j = 0; j < lines.size(); ++j) {
      switch (lines[j][i]) {
      case '0':
        zero_count++;
        break;
      case '1':
        one_count++;
        break;
      }
    }
    gamma_rate_string += (one_count > zero_count ? '1' : '0');
  }

  unsigned gamma_rate = strtoul(gamma_rate_string.c_str(), 0, 2);
  std::cout << gamma_rate_string << " " << gamma_rate << std::endl;

  std::string epsilon_rate_string{};
  for (auto i : gamma_rate_string) {
    switch (i) {
    case '0':
      epsilon_rate_string += '1';
      break;
    case '1':
      epsilon_rate_string += '0';
      break;
    }
  }
  unsigned epsilon_rate = strtoul(epsilon_rate_string.c_str(), 0, 2);

  std::cout << gamma_rate * epsilon_rate << std::endl;

  return 0;
}
