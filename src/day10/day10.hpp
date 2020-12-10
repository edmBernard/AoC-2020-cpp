
#pragma once

#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace day10 {

size_t part1(const std::vector<size_t> &list) {
  std::vector<size_t> sorted(list.begin(), list.end());
  std::sort(sorted.begin(), sorted.end());

  size_t diff1 = 0;
  size_t diff3 = 0;
  const size_t firstDiff = sorted[0] - 0;
  if (firstDiff == 1) {
    diff1 += 1;
  } else if (firstDiff == 3) {
    diff3 += 1;
  } else {
    throw std::runtime_error("difference value of " + std::to_string(firstDiff) + " unexpected");
  }
  for (size_t i = 0; i < sorted.size() - 1; ++i) {
    size_t step = sorted[i+1] - sorted[i];
    if (step == 1) {
      diff1 += 1;
    } else if (step == 3) {
      diff3 += 1;
    } else {
      throw std::runtime_error("difference value of " + std::to_string(firstDiff) + " unexpected");
    }
  }

  // the last step is always 3
  diff3 += 1;

  return diff1 * diff3;
}

size_t part2(const std::vector<size_t> &list) {
  for (auto l1 : list) {
    for (auto l2 : list) {
      for (auto l3 : list) {
        if (l1 + l2 + l3 == 2020) {
          return l1 * l2 * l3;
        }
      }
    }
  }
  return 0;
}

std::vector<size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<size_t> numberList;
  std::string line;
  while (infile >> line) {
    numberList.push_back(std::stoll(line));
  }
  return numberList;
}

} // namespace day10