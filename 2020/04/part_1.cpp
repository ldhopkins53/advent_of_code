#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

static const std::vector<std::string> required_fields = {
    "byr", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"};

bool is_valid(const std::set<std::string> &fields) {
  for (const auto i : required_fields) {
    if (fields.find(i) == fields.end()) {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv) {

  std::string filename{argv[1]};
  std::ifstream infile{filename};

  unsigned valid_passports{0};
  while (infile) {
    // Load the current passport by reading until a blank line
    std::stringstream current_passport{""};
    std::string current_line{""};
    do {
      if (!std::getline(infile, current_line)) {
        break;
      }
      current_passport << current_line << " ";
    } while (current_line != "");

    // Process the fields in the current passport
    std::set<std::string> passport_fields{};
    std::string field{};
    while (current_passport >> field) {
      auto current_field = field.substr(0, field.find(":"));
      passport_fields.insert(std::move(current_field));
    }

    if (is_valid(passport_fields)) {
      ++valid_passports;
    }
  }
  std::cout << "There are " << valid_passports << " valid passports"
            << std::endl;
  return 0;
}
