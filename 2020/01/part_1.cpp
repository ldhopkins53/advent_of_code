#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
std::pair<T, T> find_matching_numbers(const std::vector<T> &values, T target) {
  auto left = values.begin();
  auto right = values.end() - 1;
  while (left != right) {
    auto sum = *left + *right;
    if (sum > target) {
      --right;
    } else if (sum < target) {
      ++left;
    } else {
      return {*left, *right};
    }
  }
  throw std::runtime_error("Unable to find a matching pair");
}

int main(int argc, char **argv) {
  std::string filename(argv[1]);
  std::ifstream infile(filename);

  std::vector<int> values{};
  int value{0};
  while (infile >> value) {
    values.push_back(value);
  }
  std::sort(values.begin(), values.end());

  auto [left, right] = find_matching_numbers(values, 2020);
  std::cout << "The answer is: " << left * right << std::endl;
  return 0;
}
