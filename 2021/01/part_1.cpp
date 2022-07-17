#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile(filename);

  int count{0};
  int new_val{0};
  int prev_val{0};
  infile >> prev_val;
  while (infile >> new_val) {
    if (new_val > prev_val) {
      count++;
    }
    prev_val = new_val;
  }
  std::cout << count << std::endl;
  return 0;
}
