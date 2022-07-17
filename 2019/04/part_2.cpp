#include <iostream>

bool is_increasing(const std::string &candidate_string) {
  for (int i = 0; i < candidate_string.length() - 1; ++i) {
    if (candidate_string[i] > candidate_string[i + 1])
      return false;
  }
  return true;
}

bool has_repeating(const std::string &candidate_string) {
  for (int i = 0; i < candidate_string.length() - 1; ++i) {
    if (candidate_string[i] == candidate_string[i + 1]) {
      if (i - 1 >= 0 && candidate_string[i - 1] == candidate_string[i])
        continue;
      if (i + 2 < candidate_string.length() &&
          candidate_string[i + 2] == candidate_string[i + 1])
        continue;
      return true;
    }
  }
  return false;
}

int main() {
  long long left = 367479;
  long long right = 893698;

  int count{0};
  for (int candidate = left; candidate <= right; ++candidate) {
    std::string candidate_string = std::to_string(candidate);
    if (is_increasing(candidate_string) && has_repeating(candidate_string)) {
      count++;
    }
  }
  std::cout << count << std::endl;
  return 0;
}
