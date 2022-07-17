#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

std::map<int, unsigned long long> initialize_fish(std::ifstream &infile) {
  std::string number_line{};
  std::getline(infile, number_line);
  std::vector<std::string> numbers{};
  boost::split(numbers, number_line, boost::is_any_of(","),
               boost::token_compress_on);
  std::map<int, unsigned long long> fish{};
  for (const auto i : numbers) {
    auto full_number = std::stoi(i);
    if (fish.find(full_number) == fish.end()) {
      fish[full_number] = 1;
    } else {
      fish[full_number]++;
    }
  }
  fish[7] = 0;
  fish[8] = 0;
  return fish;
}

void display_map(const std::map<int, unsigned long long> &vec) {
  for (const auto &i : vec) {
    std::cout << i.first << " " << i.second << std::endl;
  }
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto fish = initialize_fish(infile);
  for (int i = 0; i < 256; ++i) {
    unsigned long long new_fish{0};
    unsigned long long add_to_next{0};

    for (int life_index = 8; life_index > 0; --life_index) {
      unsigned long long tmp = fish[life_index];
      fish[life_index] = add_to_next;
      add_to_next = tmp;
    }
    new_fish = fish[0];
    fish[6] += fish[0];
    fish[0] = add_to_next;
    fish[8] += new_fish;
  }

  display_map(fish);
  unsigned long long total{0};
  for (const auto &entry : fish) {
    total += entry.second;
  }
  std::cout << total << std::endl;

  return 0;
}
