#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include <boost/algorithm/string.hpp>

using BingoBoardLine = std::vector<std::pair<int, char>>;
using BingoBoard = std::vector<BingoBoardLine>;
using BingoBoardCollection = std::vector<BingoBoard>;

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

std::vector<int> read_in_bingo_numbers(std::ifstream &infile) {
  std::string call_order{};
  std::getline(infile, call_order);
  std::vector<std::string> numbers_from_list{};
  std::vector<int> bingo_numbers{};

  // Split csv string and convert to integers
  boost::split(numbers_from_list, call_order, boost::is_any_of(","),
               boost::token_compress_on);
  std::transform(numbers_from_list.begin(), numbers_from_list.end(),
                 std::back_inserter(bingo_numbers),
                 [](std::string s) -> int { return std::stoi(s); });

  // Clear trailing empty line for convenience
  std::getline(infile, call_order);

  return bingo_numbers;
}

BingoBoardLine create_bingo_line(std::string &current_line) {
  std::vector<std::string> line_numbers{};
  boost::split(line_numbers, current_line, boost::is_any_of(" "),
               boost::token_compress_on);
  BingoBoardLine bingo_line{};
  for (const auto i : line_numbers) {
    bingo_line.push_back({std::stoi(i), ' '});
  }
  return bingo_line;
}

BingoBoardCollection read_in_bingo_boards(std::ifstream &infile) {
  BingoBoardCollection bingo_boards{};
  while (infile) {
    BingoBoard current_board{};
    std::string current_line{""};
    while (true) {
      std::getline(infile, current_line);
      trim(current_line);
      if (current_line == "") {
        break;
      }
      BingoBoardLine bingo_line = create_bingo_line(current_line);
      current_board.push_back(std::move(bingo_line));
    }
    bingo_boards.push_back(current_board);
  }
  return bingo_boards;
}

void hit_number(BingoBoard &board, int number) {
  for (auto &line : board) {
    for (auto &entry : line) {
      if (entry.first == number) {
        entry.second = '*';
      }
    }
  }
}

bool all_hit(const BingoBoardLine &line) {
  return std::all_of(line.begin(), line.end(),
                     [](const auto &entry) { return entry.second == '*'; });
}

bool is_winner(const BingoBoard &board) {
  // Check row win
  for (int i = 0; i < board.size(); ++i) {
    const auto &row = board[i];
    if (all_hit(row)) {
      return true;
    }
  }

  // Check column win
  for (int col = 0; col < board[0].size(); ++col) {
    BingoBoardLine column{};
    for (int row = 0; row < board.size(); ++row) {
      column.push_back(board[row][col]);
    }
    if (all_hit(column)) {
      return true;
    }
  }
  return false;
}

int calculate_winner_score(const BingoBoard &board) {
  int sum{0};
  for (auto &row : board) {
    for (auto &entry : row) {
      if (entry.second != '*') {
        sum += entry.first;
      }
    }
  }
  return sum;
}

int main(int argc, char **argv) {
  std::string filename{argv[1]};
  std::ifstream infile{filename};

  auto bingo_numbers = read_in_bingo_numbers(infile);
  auto bingo_boards = read_in_bingo_boards(infile);

  auto last_winning_number = bingo_numbers[0];
  std::size_t last_winning_board = 0;
  int winning_boards{0};
  std::set<int> already_won{};
  for (const auto i : bingo_numbers) {
    for (std::size_t board_number = 0; board_number < bingo_boards.size();
         ++board_number) {
      hit_number(bingo_boards[board_number], i);
      if (is_winner(bingo_boards[board_number]) &&
          (already_won.find(board_number) == already_won.end())) {
        already_won.insert(board_number);
        winning_boards++;
        last_winning_number = i;
        last_winning_board = board_number;
        if (winning_boards == bingo_boards.size()) {
          std::cout << "The answer is: "
                    << last_winning_number *
                           calculate_winner_score(
                               bingo_boards[last_winning_board])
                    << std::endl;
          std::exit(0);
        }
      }
    }
  }
  std::cout << "The answer is: "
            << last_winning_number *
                   calculate_winner_score(bingo_boards[last_winning_board])
            << std::endl;
  std::exit(0);

  return 0;
}
