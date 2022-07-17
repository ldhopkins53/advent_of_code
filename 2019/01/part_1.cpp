#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  unsigned long long total{0};
  int mass{0};
  while (infile >> mass) {
    int fuel = ((mass / 3) - 2);
    total += fuel;
  }
  std::cout << total << std::endl;
  return 0;
}
