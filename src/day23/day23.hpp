
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
    cups.reserve(line.length());
    for (char c : line) {
      // we start index to 0 so we will have to add 1 for output
      cups.push_back(c - '1');
    }

    // try to consider a chain list like
    index = std::vector<int>(maxDim, 0);
    std::iota(index.begin(), index.end(), 1);

    // content of the current is the next position
    for (int i = 1; i < line.size(); ++i) {
      index[cups[i-1]] = cups[i];
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

  int64_t getResultPart1() {
    int64_t res = index[0]+1;
    int64_t len = index.size() - 1; // skip the 1
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

  void run(size_t iterations) {

    for (int i = 0; i < iterations; ++i) {

      const int pick1 = index[currentIdx];
      const int pick2 = index[pick1];
      const int pick3 = index[pick2]; // position of pick3

      // find insert point
      int min = currentIdx;
      do {
        min = (min == 0 ? index.size() : min) - 1;
      } while (min == pick1 || min == pick2 || min == pick3);

      // cut and reconnect linked list
      currentIdx = index[currentIdx] = std::exchange(index[pick3], std::exchange(index[min], pick1));
    }
  }

  int currentIdx;
  std::vector<int> cups;
  std::vector<int> index;
};


size_t part1(const std::string &line) {

  Board board(line, line.length());

  board.run(100);

  return board.getResultPart1();
}

size_t part2(const std::string &line) {

  Board board(line, 1'000'000);

  board.run(10'000'000);

  auto [number1, number2] = board.getResultPart2();

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