
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
  Board(std::vector<int> cups) : cups(cups) {}
  Board(std::string line) {
      cups.reserve(line.length());
      for (char c : line) cups.push_back(c - '0');
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

  std::vector<int> aligned() {
    auto found = std::find(cups.begin(), cups.end(), 1);
    const size_t step = found - cups.begin();
    std::vector<int> res(cups.size(), 0);
    for (int i = 0; i < cups.size(); ++i) {
      res[i] = cups[offset(i+step)];
    }
    return res;
  }

  int64_t getResult() {
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

    std::vector<int> next(cups.size(), 0);
    std::vector<int64_t> index(cups.size(), 0);
    std::iota(index.begin(), index.end(), 0);

    // show();

    // show(index);
    index[offset(currentIdx+1)] += currentIdx + insertPoint - 3;
    index[offset(currentIdx+2)] += currentIdx + insertPoint - 3;
    index[offset(currentIdx+3)] += currentIdx + insertPoint - 3;
    // show(index);
    for (int i = currentIdx+4; i < insertPoint+1; ++i) {
      index[offset(i)] -= 3;
    }
    // show(index);

    for (int i = 0; i < index.size(); ++i) {
      index[i] -= 1;
    }
    // show(index);
    for (int i = 0; i < next.size(); ++i) {
      next[offset(index[i])] = cups[i];
    }
    cups = next;


    // std::cout << "next.size(): " << next.size() << std::endl;
    // int insertedValue = 0;
    // for (int i = 0, index = 0; i < cups.size(); ++i, ++index) {
    //   // Can be a switch with passthough
    //   if (index == pick1) ++index;
    //   if (index == pick2) ++index;
    //   if (index == pick3) ++index;

    //   if (insertedValue < 3) {

    //     if (index == insertPoint+1) {
    //       next[i] = cups[offset(pick1)];
    //       ++insertedValue;
    //     } else if (index == insertPoint+2) {
    //       next[i] = cups[offset(pick2)];
    //       ++insertedValue;
    //     } else if (index == insertPoint+3) {
    //       next[i] = cups[offset(pick3)];
    //       ++insertedValue;
    //     } else {
    //       next[i] = cups[offset(index)];
    //     }
    //     if (insertedValue == 3) {
    //       index -= 3;
    //     }
    //   } else {
    //     next[i] = cups[offset(index)];
    //   }

    // }
    // currentIdx = offset(currentIdx+1);

  }

  size_t currentIdx = 0;
  std::vector<int> cups;
};

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  getline(infile, line);
  Board board(line);

  board.show();
  for (int i = 0; i < 100; ++i) {
    board.flip();
    // board.show();
    // board.show(board.aligned());
    // std::cout << "board.getResult(): " << board.getResult() << std::endl;
  }
  board.show();
    // std::cout << "board.getResult(): " << board.getResult() << std::endl;
  size_t startPosition = std::stoi(line);

  size_t part1 = board.getResult();

  size_t part2 = 0;
  return {part1, part2};
}

} // namespace day23