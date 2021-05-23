
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

struct Board {
  Board(std::string line, size_t maxDim) {
    // Add input to vector
    cups.reserve(maxDim);
    for (char c : line) {
      // we start index to 0 so we will have to add 1 for output
      cups.push_back(c - '1');
    }

    // try to consider a chain list like
    index = std::vector<int64_t>(maxDim, 0);
    std::iota(index.begin(), index.end(), 1);

    // content of the current is the next position
    for (int i = 1; i < line.size(); ++i) {
      index[offset(cups[i-1])] = cups[i];
    }

    // we connect last position to first position
    if (index.size() == cups.size()) {
      index[cups.back()] = cups[0];
    } else {
      index[cups.back()] = cups.size();
      index[index.size() - 1] = cups[0];
    }
    currentIdx = cups[0];
  }

  size_t offset(size_t index) {
    return (index + cups.size()) % cups.size();
  }

  int circleValue(int64_t value) {
    return value < 1 ? cups.size() : (value > cups.size() ? 1 : value);
  }

  void show() {
    for (int i = 0; i < cups.size(); ++i) {
      if (i == currentIdx) std::cout << "(" << cups[i]+1 << ") ";
      else std::cout << cups[i]+1 << " ";
    }
    std::cout << std::endl;
  }
  void chain() {
    int64_t len = index.size();
    std::cout << "(" << currentIdx+1 << ")" << " ";
    int64_t i = currentIdx;
    while (--len) {
      std::cout << index[i]+1 << " ";
      i = index[i];
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
    int64_t res = index[0]+1;
    int64_t len = index.size() - 1;
    int64_t i = index[0];
    while (--len) {
      res = res * 10 + index[i]+1;
      i = index[i];
    }
    return res;
  }
  std::pair<int64_t, int64_t> getResultPart2() {
    return {index[0] + 1 , index[index[0]] + 1};
  }

  void flip() {

    const int64_t pick1 = index[currentIdx];
    const int64_t pick2 = index[pick1];
    const int64_t pick3 = index[pick2]; // position of pick3

    // find insert point
    int64_t min = currentIdx;
    do {
      min = (min == 0 ? index.size() : min) - 1;
    } while (min == pick1 || min == pick2 || min == pick3);

    // cut and reconnect linked list
    currentIdx = index[currentIdx] = index[pick3];
    index[pick3] = index[min];
    index[min] = pick1;


  }

  int64_t currentIdx;
  std::vector<int64_t> cups;
  std::vector<int64_t> index;
};


size_t part1(const std::string &line) {

  Board boardPart1(line, line.length());

  for (int i = 0; i < 100; ++i) {
    boardPart1.flip();
  }

  return boardPart1.getResultPart1();
}

size_t part2(const std::string &line) {

  Board boardPart2(line, 1'000'000);

  for (int i = 0; i < 10'000'000; ++i) {
    boardPart2.flip();
  }

  auto [number1, number2] = boardPart2.getResultPart2();

  return  number1 * number2;
}



std::string parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  getline(infile, line);

  return line;
}

} // namespace day23