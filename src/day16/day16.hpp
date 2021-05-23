
#pragma once

#include <algorithm>
#include <bitset>
#include <charconv>
#include <exception>
#include <fstream>
#include <memory>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <array>

namespace day16 {

void showMatrix(const std::vector<std::vector<bool>> &matrix) {
  std::cout << std::endl;
  for (auto row : matrix) {
    for (auto i : row) {
      std::cout << (i ? 1 : 0) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

size_t part1(const std::tuple<uint64_t, uint64_t> &results) {
  return std::get<0>(results);
}

uint64_t part2(const std::tuple<uint64_t, uint64_t> &results) {

  return std::get<1>(results);
}

std::tuple<uint64_t, uint64_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  uint64_t part1Result = 0;
  std::string line;
  std::vector<std::array<int, 4>> matchingRules;
  std::vector<int> myTicket;
  std::regex rulesRegex("(.+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");
  std::vector<std::vector<bool>> matchingFieldMatrix;
  std::vector<std::string> fieldName;

  while (getline(infile, line)) {
    std::smatch match;
    if (std::regex_match(line, match, rulesRegex)) {
      // Parsing of Line with Memory
      const int min1 = std::stoi(match[2]);
      const int max1 = std::stoi(match[3]);
      const int min2 = std::stoi(match[4]);
      const int max2 = std::stoi(match[5]);

      matchingRules.push_back({min1, max1, min2, max2});
      fieldName.push_back(match[1].str());
    } else if (line == "your ticket:") {
      // initialize match matrix
      for (const auto &i: matchingRules) {
        matchingFieldMatrix.push_back(std::vector<bool>(matchingRules.size(), true));
      }

      infile >> line;
      std::stringstream ssLine(line);
      std::string number_s;
      while (std::getline(ssLine, number_s, ',')) {
        const int number = std::stoi(number_s);
        myTicket.push_back(number);
      }
    } else if (line == "nearby tickets:") {
      while (getline(infile, line)) {
        std::stringstream ssLine(line);
        std::string number_s;
        int columnNumber = 0;
        while (std::getline(ssLine, number_s, ',')) {
          const int number = std::stoi(number_s);
          bool haveValid = false;
          for (auto [min1, max1, min2, max2] : matchingRules) {
            if (((number >= min1 && number <= max1) || (number >= min2 && number <= max2))) {
              haveValid = true;
            }
          }
          if (!haveValid) {
            part1Result += number;
          } else {

            // can be done on the same loop but lazy
            for (int i = 0; i < matchingRules.size(); ++i) {
              const auto [min1, max1, min2, max2] = matchingRules[i];
              if (!((number >= min1 && number <= max1) || (number >= min2 && number <= max2))) {
                matchingFieldMatrix[i][columnNumber] = false;
              }
            }
          }
          ++columnNumber;
        }
      }
    }
  }

  // loop to determine value with ambiguity
  for (int notUsed = 0; notUsed < matchingRules.size(); ++notUsed) {
    // loop to be sure we propagate on all field

    for (int n = 0; n < matchingRules.size(); ++n) {
      int lastTrueIndex = -1;
      for (int i = 0; i < matchingRules.size(); ++i) {
        if (matchingFieldMatrix[n][i] == true && lastTrueIndex == -1) {
          lastTrueIndex = i;
        } else if (matchingFieldMatrix[n][i] == true && lastTrueIndex != -1) {
          lastTrueIndex = -1;
          break;
        }
      }

      if (lastTrueIndex != -1) {
        for (int m = 0; m < matchingRules.size(); ++m) {
          if (m!=n) {
            matchingFieldMatrix[m][lastTrueIndex] = false;
          }
        }
      }
    }
  }

  uint64_t part2Result = 1;
  for (int i = 0; i < matchingRules.size(); ++i) {
    std::string_view departure(fieldName[i].data(), fieldName[i].data() + 9);
    if (departure == "departure") {
      for (int j = 0; j < matchingRules.size(); ++j) {
        if (matchingFieldMatrix[i][j] == true) {
          part2Result *= myTicket[j];
        }
      }
    }
  }
  return {part1Result, part2Result};
}

} // namespace day16