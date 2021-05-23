
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

  static int circleValue(int value) {
    return value < 1 ? 9 : (value > 9 ? 1 : value);
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
    size_t pick1 = offset(currentIdx+1);
    size_t pick2 = offset(currentIdx+2);
    size_t pick3 = offset(currentIdx+3);
    int min = cups[currentIdx];
    // std::cout << "pickup: " << cups[pick1] << ", " << cups[pick2] << ", " << cups[pick3] << std::endl;
    auto newPosition = cups.end();
    do {
      min = circleValue(min-1);
      newPosition = std::find(cups.begin(), cups.end(), min);
    } while (
      newPosition == cups.end()
      || newPosition == cups.begin()+pick1
      || newPosition == cups.begin()+pick2
      || newPosition == cups.begin()+pick3);

    size_t insertPoint = newPosition - cups.begin();

    // std::cout << "min: " << min << std::endl;
    // std::cout << "newPosition: " << insertPoint << std::endl;

    std::vector<int64_t> next(cups.size(), 0);
    std::vector<int64_t> index(cups.size(), 0);
    std::iota(index.begin(), index.end(), 0);

    // show();

    // show(index);
    index[offset(currentIdx+1)] += currentIdx + insertPoint - 3;
    index[offset(currentIdx+2)] += currentIdx + insertPoint - 3;
    index[offset(currentIdx+3)] += currentIdx + insertPoint - 3;
    // show(index);
    for (int64_t i = currentIdx+4; i < insertPoint+1; ++i) {
      index[offset(i)] -= 3;
    }
    // show(index);

    for (int64_t i = 0; i < index.size(); ++i) {
      index[i] -= 1;
    }
    // show(index);
    for (int64_t i = 0; i < next.size(); ++i) {
      next[offset(index[i])] = cups[i];
    }
    cups = next;

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

  // Part2
  Board boardPart2(line, 1000000);

  // boardPart2.show();
  for (int i = 0; i < 10000000; ++i) {
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