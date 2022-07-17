#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile(filename);

  unsigned valid_passwords{0};
  std::string range{};
  std::string character_identifier{};
  std::string password{};
  while (infile >> range >> character_identifier >> password) {
    std::vector<std::string> split_range{};
    split(split_range, range, boost::is_any_of("-"), boost::token_compress_on);
    int lower = std::stoi(split_range[0]);
    int upper = std::stoi(split_range[1]);
    int char_count{0};
    for (auto i : password) {
      if (i == character_identifier[0]) {
        ++char_count;
      }
    }
    if ((char_count <= upper) && (char_count >= lower)) {
      ++valid_passwords;
    }
  }
  std::cout << valid_passwords << " valid passwords" << std::endl;
  return 0;
}
