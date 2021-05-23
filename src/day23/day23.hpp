
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
#include <numeric>

namespace day23 {



size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}

struct Board {
  Board(std::string line) {
    cups.reserve(line.length());
    for (char c : line) cups.push_back(c - '0');
  }
  Board(std::string line, size_t maxDim) {
    cups.reserve(maxDim);
    for (char c : line) {
      cups.push_back(c - '0');
    }
    for (int i = line.length(); i < maxDim; ++i) {
      cups.push_back(i);
    }
  }

  size_t offset(size_t index) {
    return (index + cups.size()) % cups.size();
  }

  int circleValue(int64_t value) {
    return value < 1 ? cups.size() : (value > cups.size() ? 1 : value);
  }

  void show() {
    for (int i = 0; i < cups.size(); ++i) {
      if (i == currentIdx) std::cout << "(" << cups[i] << ") ";
      else std::cout << cups[i] << " ";
    }
    std::cout << std::endl;
  }

  template <typename T>
  static void show(std::vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
  }

  int64_t getResultPart1() {
    auto found = std::find(cups.begin(), cups.end(), 1);
    const size_t step = found - cups.begin();
    int64_t res = 0;
    int64_t power = 1;
    for (int i = cups.size() - 1; i > 0; --i) {
      // 1 should be removed
      res += cups[offset(i+step)] * power;
      power *= 10;
    }
    return res;
  }
  std::pair<int64_t, int64_t> getResultPart2() {
    auto found = std::find(cups.begin(), cups.end(), 1);
    return {*(found+1), *(found+2)};
  }

  void flip() {
    const int64_t pick1 = cups[offset(currentIdx+1)];
    const int64_t pick2 = cups[offset(currentIdx+2)];
    const int64_t pick3 = cups[offset(currentIdx+3)];

    int64_t min = cups[currentIdx];

    do {
      min = circleValue(min-1);
    } while (min == pick1 || min == pick2 || min == pick3);

    const auto newPosition = std::find(cups.begin(), cups.end(), min);

    size_t insertPoint = newPosition - cups.begin();

    if (currentIdx > insertPoint) {
      insertPoint += cups.size();
    }
    for (int64_t i = currentIdx+4; i < insertPoint + 1; ++i) {
      cups[offset(i-3)] = cups[offset(i)];
    }
    cups[offset(insertPoint + 1 - 3)] = pick1;
    cups[offset(insertPoint + 2 - 3)] = pick2;
    cups[offset(insertPoint + 3 - 3)] = pick3;

    currentIdx = offset(currentIdx+1);
  }

  size_t currentIdx = 0;
  std::vector<int64_t> cups;
};

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  getline(infile, line);
  Board boardPart1(line);

  //Part1
  boardPart1.show();
  for (int i = 0; i < 100; ++i) {
    boardPart1.flip();
  }
  boardPart1.show();

  size_t part1 = boardPart1.getResultPart1();
  std::cout << "part1: " << part1 << std::endl;

  // Part2
  Board boardPart2(line, 1'000'000);

  for (int i = 0; i < 10'000'000; ++i) {
    if (i % 1000 == 0) {
      std::cout << "i: " << i << std::endl;
    }
    boardPart2.flip();
  }
  // boardPart2.show();

  auto [number1, number2] = boardPart2.getResultPart2();
  std::cout << "number1: " << number1 << std::endl;
  std::cout << "number2: " << number2 << std::endl;
  size_t part2 = number1 * number2;
  std::cout << "part2: " << part2 << std::endl;

  return {part1, part2};
}

} // namespace day23