#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

template <typename T>
std::vector<T>
do_multiple_intersections(const std::vector<std::vector<T>> &group) {
  std::vector<T> current_intersection{group[0]};
  for (auto i = 1; i < group.size(); ++i) {
    std::vector<T> new_intersection{};
    std::set_intersection(current_intersection.cbegin(),
                          current_intersection.cend(), group[i].cbegin(),
                          group[i].cend(),
                          std::back_inserter(new_intersection));
    std::swap(current_intersection, new_intersection);
  }
  return current_intersection;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  std::vector<unsigned> group_counts{};
  while (infile) // Keep reading until we run out of entries
  {
    std::vector<std::vector<char>> current_group{};
    std::string current_person{};
    std::getline(infile, current_person);
    do { // Read each person in the group
      std::vector<char> person_vector{current_person.cbegin(),
                                      current_person.cend()};
      std::sort(person_vector.begin(), person_vector.end());
      current_group.push_back(person_vector);
      std::getline(infile, current_person);
    } while (current_person != "");
    auto intersection = do_multiple_intersections(current_group);
    group_counts.push_back(intersection.size());
  }

  auto sum_of_elems =
      std::accumulate(group_counts.cbegin(), group_counts.cend(), 0);
  std::cout << "The answer is: " << sum_of_elems << std::endl;
  return 0;
}
