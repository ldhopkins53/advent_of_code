#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile(filename);

  // Setup initial starting sum
  int a, b, c;
  infile >> a >> b >> c;
  auto prev_sum = a + b + c;

  auto count{0};
  int new_c;
  while (infile >> new_c) {
    auto new_sum = (prev_sum - a) + new_c;
    a = b;
    b = c;
    c = new_c;
    if (new_sum > prev_sum) {
      count++;
    }
    prev_sum = new_sum;
  }

  std::cout << count << std::endl;
  return 0;
}
