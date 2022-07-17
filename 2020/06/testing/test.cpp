#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

template <typename T> void display_iterable(T s) {
  for (const auto i : s) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::set<int> x{1, 2, 3};
  std::set<int> y{2, 3, 4};
  std::vector<int> output{};
  std::set_intersection(x.begin(), x.end(), y.begin(), y.end(),
                        std::back_inserter(output));

  display_iterable(output);
}
