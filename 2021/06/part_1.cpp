#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

std::vector<int> initialize_fish(std::ifstream &infile) {
  std::string number_line{};
  std::getline(infile, number_line);
  std::vector<std::string> numbers{};
  boost::split(numbers, number_line, boost::is_any_of(","),
               boost::token_compress_on);
  std::vector<int> fish{};
  std::transform(numbers.begin(), numbers.end(), std::back_inserter(fish),
                 [](const std::string &i) { return std::stoi(i); });
  return fish;
}

template <typename T> void display_vector(const std::vector<T> &vec) {
  for (const auto &i : vec) {
    std::cout << i << ",";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto fish = initialize_fish(infile);
  for (int i = 0; i < 80; ++i) {
    std::cout << "Executing step: " << i + 1 << std::endl;
    unsigned fish_to_add{0};
    for (std::size_t fish_index = 0; fish_index < fish.size(); ++fish_index) {
      auto current_fish = fish[fish_index];
      if (current_fish == 0) {
        fish[fish_index] = 6;
        fish_to_add++;
      } else {
        fish[fish_index]--;
      }
    }

    for (int f = 0; f < fish_to_add; ++f) {
      fish.push_back(8);
    }
  }

  std::cout << fish.size() << std::endl;

  return 0;
}
