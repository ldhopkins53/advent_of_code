#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  long long current{0};
  long long total{0};
  while (infile >> current) {
    total += current;
  }
  std::cout << total << std::endl;
  return 0;
}
