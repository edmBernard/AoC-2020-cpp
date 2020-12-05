
#pragma once

#include <algorithm>
#include <array>
#include <charconv>
#include <exception>
#include <fstream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace day5 {

int part1(const std::vector<int> &boardingPassIDs) {
  int maxID = 0;
  for (auto id : boardingPassIDs) {
    if (id > maxID) {
      maxID = id;
    }
  }
  return maxID;
}

int part2(const std::vector<int> &boardingPassIDs) {
  int maxID = 0;
  std::vector<int> sortedIDs(boardingPassIDs.begin(), boardingPassIDs.end());
  std::sort(sortedIDs.begin(), sortedIDs.end());

  for (size_t i = 0; i < sortedIDs.size() - 1; ++i) {
    if (sortedIDs[i+1] - sortedIDs[i] == 2) {
      return sortedIDs[i]+1;
    }
  }
  return -1;
}


int binaryToInt(std::string_view seatStr, int base, char one) {
  const int digit = (seatStr[0]==one) << base;
  if (base > 0) {
    return digit + binaryToInt(seatStr.data() + 1, base - 1, one);
  } else {
    return digit;
  }
}



std::vector<int> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<int> boardingPassIDs;
  std::string line;
  while (getline(infile, line)) {
    boardingPassIDs.push_back(8 * binaryToInt(line.data(), 6, 'B') + binaryToInt(line.data()+7, 2, 'R'));
  }

  return boardingPassIDs;
}

} // namespace day4