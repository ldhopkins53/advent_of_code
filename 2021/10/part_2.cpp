#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

static const std::map<char, char> closer_delimiter_mapping{
    {')', '('}, {'>', '<'}, {']', '['}, {'}', '{'}};
static const std::map<char, char> opener_delimiter_mapping{
    {'(', ')'}, {'<', '>'}, {'[', ']'}, {'{', '}'}};
static const std::map<char, int> error_score_map{
    {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

std::vector<char> build_error_string(std::stack<char> s) {
  std::vector<char> required_characters{};
  while (!s.empty()) {
    required_characters.push_back(opener_delimiter_mapping.at(s.top()));
    s.pop();
  }
  return required_characters;
}

std::pair<std::stack<char>, bool>
check_for_corruption(const std::string &line) {
  std::stack<char> s{};
  for (const char c : line) {
    if (closer_delimiter_mapping.find(c) == closer_delimiter_mapping.end()) {
      // Opening character
      s.push(c);
      continue;
    }
    // Found a closing character
    if (s.top() != closer_delimiter_mapping.at(c)) {
      return {s, true};
    }
    s.pop();
  }
  return {s, false};
}

long long unsigned
calculate_error_score(const std::vector<char> &required_characters) {
  long long unsigned error_score{0};
  for (const auto i : required_characters) {
    error_score = (5 * error_score) + error_score_map.at(i);
  }
  return error_score;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::string line{};
  std::vector<long long unsigned> error_scores{};
  while (std::getline(infile, line)) {
    auto [remaining_characters, is_corrupted] = check_for_corruption(line);
    if (is_corrupted) {
      continue;
    }
    // Line is not corrupted, just incomplete
    auto required_characters = build_error_string(remaining_characters);
    auto error_score = calculate_error_score(required_characters);
    error_scores.push_back(error_score);
  }

  //
  std::size_t median_position = error_scores.size() / 2;
  std::nth_element(error_scores.begin(), error_scores.begin() + median_position,
                   error_scores.end());
  std::cout << "The answer is: " << error_scores[median_position] << std::endl;
  return 0;
}
