
#pragma once

#include <algorithm>
#include <charconv>
#include <exception>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <numeric>
#include <regex>
#include <bitset>

namespace day14 {

size_t part1(const std::tuple<std::map<uint64_t, uint64_t>, std::map<uint64_t, uint64_t>>& memory) {
  uint64_t count = 0;
  for (auto [k, v] : std::get<0>(memory)) {
    count += v;
  }
  return count;
}


size_t part2(const std::tuple<std::map<uint64_t, uint64_t>, std::map<uint64_t, uint64_t>>  &memory) {
  uint64_t count = 0;
  for (auto [k, v] : std::get<1>(memory)) {
    count += v;
  }
  return count;
}

std::tuple<std::map<uint64_t, uint64_t>, std::map<uint64_t, uint64_t>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;

  std::regex maskRegex("mask = ([0-1X]+)");
  std::regex memRegex("mem\\[([0-9]+)\\] = ([0-9]+)");
  uint64_t maskPositive = 0; // Mask with X replaced by 0
  uint64_t maskNegative = 0; // Mask with X replaced by 1
  uint64_t floatingMask = 0; // Mask that indicate X with 1
  std::smatch match;
  std::map<uint64_t, uint64_t> memoryPart1;
  std::map<uint64_t, uint64_t> memoryPart2;
  while (getline(infile, line)) {
    if (std::regex_match(line, match, memRegex)) {
      memoryPart1[std::stoi(match[1])] = std::stoi(match[2]) & maskNegative | maskPositive;

      // ugly solution with bit arithmetic
      // Loop on number of X
      for (size_t i = 0; i < (1 << std::bitset<36>(floatingMask).count()); ++i) {
        int count = 0;
        uint64_t mask = 0;
        // Loop on position in Mask
        for (size_t j = 0; j < 36; ++j) {
          if ((floatingMask >> j) & 1 ) {
            mask += (((i>>count) & 1) << j);
            ++count;
          }
        }
        uint64_t memoryAddress = ((std::stoi(match[1]) & ~floatingMask) | mask | maskPositive);
        memoryPart2[memoryAddress] = std::stoi(match[2]);
      }
    } else if (std::regex_match(line, match, maskRegex)) {
      maskPositive = 0;
      maskNegative = 0;
      floatingMask = 0;
      const std::string mask = match[1].str();
      for (size_t i = 0; i < mask.size(); ++i) {
        maskNegative <<= 1;
        maskPositive <<= 1;
        floatingMask <<= 1;
        if (mask[i] == 'X') {
          maskNegative += 1;
          floatingMask += 1;
        } else {
          maskNegative += int(mask[i]=='1');
          maskPositive += int(mask[i]=='1');
        }
      }
    }
  }

  return {memoryPart1, memoryPart2};
}

} // namespace day14