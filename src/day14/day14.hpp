
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

size_t part1(const std::map<uint64_t, uint64_t>& memory) {
  uint64_t count = 0;
  for (auto [k, v] : memory) {
    count += v;
  }
  return count;
}


size_t part2(const std::map<uint64_t, uint64_t>  &memory) {

  return 0;
}

std::map<uint64_t, uint64_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;

  std::regex maskRegex("mask = ([0-1X]+)");
  std::regex memRegex("mem\\[([0-9]+)\\] = ([0-9]+)");
  uint64_t maskPositive = 0;
  uint64_t maskNegative = 0;
  std::vector<uint64_t> memPosition;
  std::vector<uint64_t> memValue;
  std::smatch match;
  std::map<uint64_t, uint64_t> memory;
  while (getline(infile, line)) {
    if (std::regex_match(line, match, memRegex)) {
      memory[std::stoi(match[1])] = std::stoi(match[2]) & maskNegative | maskPositive;
    } else if (std::regex_match(line, match, maskRegex)) {
      maskPositive = 0;
      maskNegative = 0;
      const std::string mask = match[1].str();
      for (int i = 0; i < mask.size(); ++i) {
        maskNegative <<= 1;
        maskPositive <<= 1;
        if (mask[i] == 'X') {
          maskNegative += 1;
        } else {
          maskNegative += int(mask[i]=='1');
          maskPositive += int(mask[i]=='1');
        }
      }
    }
  }

  return memory;
}

} // namespace day14