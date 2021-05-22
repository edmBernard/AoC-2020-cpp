
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <regex>

namespace day25 {



size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}

inline size_t loop(size_t value, size_t subjectNumber) {
  return (value * subjectNumber) % 20201227;
}

int getLoopSize(size_t key, size_t subjectNumber) {
  size_t value = 1;
  int loopSize = 0;
  while (value != key) {
    value = loop(value, subjectNumber);
    ++loopSize;
  }
  return loopSize;
}

size_t encrypt(size_t subjectNumber, size_t loopSize) {
  size_t value = 1;
  for (int i = 0; i < loopSize; ++i) {
    value = loop(value, subjectNumber);
  }
  return value;
}

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  getline(infile, line);
  size_t key1 = std::stoi(line);
  getline(infile, line);
  size_t key2 = std::stoi(line);

  size_t part1 = encrypt(key1, getLoopSize(key2, 7));

  size_t part2 = 0;
  return {part1, part2};
}

} // namespace day25