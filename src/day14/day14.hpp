
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

size_t part1(const std::tuple<std::unordered_map<uint64_t, uint64_t>, std::unordered_map<uint64_t, uint64_t>>& memory) {
  uint64_t count = 0;
  for (auto [k, v] : std::get<0>(memory)) {
    count += v;
  }
  return count;
}


size_t part2(const std::tuple<std::unordered_map<uint64_t, uint64_t>, std::unordered_map<uint64_t, uint64_t>>  &memory) {
  uint64_t count = 0;
  for (auto [k, v] : std::get<1>(memory)) {
    count += v;
  }
  return count;
}

std::tuple<std::unordered_map<uint64_t, uint64_t>, std::unordered_map<uint64_t, uint64_t>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::regex memRegex("mem\\[([0-9]+)\\] = ([0-9]+)");
  std::smatch match;

  uint64_t maskPositive = 0; // Mask with X replaced by 0
  uint64_t maskNegative = 0; // Mask with X replaced by 1
  uint64_t wildcardMask = 0; // Mask with X positions
  std::vector<uint64_t> floatingMask; // all mask generated with wildcard replaced
  std::unordered_map<uint64_t, uint64_t> memoryPart1;
  std::unordered_map<uint64_t, uint64_t> memoryPart2;

  while (getline(infile, line)) {

    if (line[1] == 'a') {
      // match the m"a"sk line
      std::string_view mask_s(line.data() + 7, 36);
      // Parsing of Line with Mask
      maskPositive = 0;
      maskNegative = 0;
      wildcardMask = 0; // Mask with X position
      floatingMask.clear();
      for (char c : mask_s) {
        maskNegative <<= 1;
        maskPositive <<= 1;
        wildcardMask <<= 1;
        if (c == 'X') {
          maskNegative += 1;
          wildcardMask += 1;
        } else {
          maskNegative += int(c=='1');
          maskPositive += int(c=='1');
        }
      }

      // build floating mask
      for (size_t i = 0; i < (1 << std::bitset<36>(wildcardMask).count()); ++i) {
        int count = 0;
        uint64_t mask = 0;
        // Loop on position in Mask
        for (size_t j = 0; j < 36; ++j) {
          if ((wildcardMask >> j) & 1 ) {
            mask += (((i>>count) & 1) << j);
            ++count;
          }
        }
        floatingMask.push_back(mask);
      }
    } else if (std::regex_match(line, match, memRegex)) {
      // Parsing of Line with Memory
      const int mem = std::stoi(match[1]);
      const int value = std::stoi(match[2]);

      memoryPart1[mem] = value & maskNegative | maskPositive;

      for (uint64_t mask : floatingMask) {
        const uint64_t memoryAddress = mem & ~wildcardMask | mask | maskPositive;
        memoryPart2[memoryAddress] = value;
      }
    }

  }

  return {memoryPart1, memoryPart2};
}

} // namespace day14