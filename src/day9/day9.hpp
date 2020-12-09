
#pragma once

#include <algorithm>
#include <fstream>
#include <numeric>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace day9 {

bool isValid(int64_t number, std::span<const int64_t> numbersList) {

  for (auto i : numbersList) {
    for (auto j : numbersList) {
      if (i + j == number && i != j) {
        return true;
      }
    }
  }
  return false;
}

int64_t part1(const std::vector<int64_t> &numbers, size_t preamble = 25) {
  int accumulator = 0;
  for (auto it = numbers.begin(); it < numbers.end() - preamble; ++it) {
    if (!isValid(*(it + preamble), {it, preamble})) {
      return *(it + preamble);
    }
  }
  return 0;
}

int64_t part2(const std::vector<int64_t> &numbers, size_t preamble = 25) {
  int64_t invalidNumber = part1(numbers, preamble);
  for (auto it = numbers.begin(); it < numbers.end(); ++it) {
    for (size_t i = 0; i < size_t(numbers.end() - it); ++i) {
      if (std::accumulate(it, it + i, int64_t(0)) == invalidNumber) {
        auto [min, max] = std::minmax_element(it, it + i);
        return *min + *max;
      }
    }
  }
  return 0;
}

std::vector<int64_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::vector<int64_t> numbers;

  while (getline(infile, line)) {
    int64_t value = std::stoll(line);
    numbers.push_back(value);
  }

  return numbers;
}

} // namespace day9