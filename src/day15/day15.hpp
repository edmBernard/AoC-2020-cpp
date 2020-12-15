
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

namespace day15 {

size_t part1(const std::vector<int> &inputs) {
  std::vector<int> numbers(inputs.begin(), inputs.end());
  numbers.reserve(2020);

  uint64_t count = 0;
  while (numbers.size() < 2020) {
    auto it1 = std::find(numbers.rbegin(), numbers.rend(), numbers[numbers.size()-1]);
    if (it1 != numbers.rend()) {
      auto it2 = std::find(it1 + 1, numbers.rend(), numbers[numbers.size()-1]);
      if (it2 != numbers.rend()) {
        numbers.push_back(it2 - it1);
      } else {
        numbers.push_back(0);
      }
    } else {
      numbers.push_back(0);
    }

  }

  return numbers[numbers.size() - 1];
}

uint64_t part2(const std::vector<int> &inputs) {

  std::unordered_map<uint64_t, uint64_t> numbers;
  uint64_t lastNumber;
  uint64_t previousPosition = 0;
  for (size_t i = 0; i < inputs.size(); ++i) {
    numbers[inputs[i]] = i + 1; // shift time from 1 too keep 0 as unknown position
    lastNumber = inputs[i];
  }

  for (size_t i = inputs.size() + 1; i <= 30000000; ++i) {
    uint64_t currentNumber;
    if (previousPosition != 0) {
      currentNumber = i - 1 - previousPosition;
    } else {
      currentNumber = 0;
    }
    lastNumber = currentNumber;
    if (numbers.count(currentNumber)){
      previousPosition = numbers[currentNumber];
    } else {
      previousPosition = 0;
    }
    numbers[currentNumber] = i;
  }

  return lastNumber;
}

std::vector<int> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::vector<int> spokenNumbers;

  while (getline(infile, line)) {
    std::stringstream ss(line);
    std::string number_s;
    while (std::getline(ss, number_s, ',')) {
      spokenNumbers.push_back(std::stoi(number_s));
    }
  }

  return spokenNumbers;
}

} // namespace day15