
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
#include <array>
#include <regex>

namespace day24 {

size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}


struct Point {
  int x;
  int y;

  bool operator<(const Point& rhs) const {
    if (x != rhs.x) {
      return x < rhs.x;
    }
    return y < rhs.y;
  }

  int move(std::string_view s) {
    // e, se, sw, w, nw, and ne
    if (s.substr(0, 1) == "e") {
      x += 1;
      return 1;
    } else if (s.substr(0, 2) == "se") {
      x += 1;
      y -= 1;
      return 2;
    } else if (s.substr(0, 2) == "sw") {
      y -= 1;
      return 2;
    } else if (s.substr(0, 1) == "w") {
      x -= 1;
      return 1;
    } else if (s.substr(0, 2) == "nw") {
      x -= 1;
      y += 1;
      return 2;
    } else if (s.substr(0, 2) == "ne") {
      y += 1;
      return 2;
    }
    throw std::runtime_error("Unknown direction");
  }
};

struct Board {
  Board(int64_t width, int64_t height)
  : width(width)
  , height(height)
  , buffer(width*height, 0)
  , center(width/2 + height/2*width) {
  }

  inline size_t offset(int64_t x, int64_t y) {
    return center + x + y * width;
  }

  uint8_t &operator()(int64_t x, int64_t y) {
    return buffer[offset(x, y)];
  }
  uint8_t &operator()(const Point &pt) {
    return buffer[offset(pt.x, pt.y)];
  }
  uint8_t &operator()(size_t address) {
    return buffer[address];
  }

  int countNeighbors(size_t address) {
    return (
      buffer[address + 1] +
      buffer[address - 1] +
      buffer[address + width] +
      buffer[address - width] +
      buffer[address + 1 - width] +
      buffer[address - 1 + width]);
  }

  std::array<size_t, 6> getNeighbors(size_t address) {
    return {
      address + 1,
      address - 1,
      address + width,
      address - width,
      address + 1 - width,
      address - 1 + width
    };
  }

  void flip(size_t address) {
    uint8_t& color = this->operator()(address);
    color = color == 0 ? 1 : 0;
  }

  void flip(size_t x, size_t y) {
    uint8_t& color = this->operator()(x, y);
    color = color == 0 ? 1 : 0;
  }

  int64_t width;
  int64_t height;
  int64_t center;
  std::vector<uint8_t> buffer;
};

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  Board board(500, 500);

  while (getline(infile, line)) {
    Point pt{0, 0};
    for (int i = 0; i < line.length();) {
      i += pt.move(line.substr(i));
    }
    board.flip(pt.x, pt.y);
  }

  size_t part1 = 0;
  for (auto i : board.buffer) {
    part1 += i;
  }

  for (int epoch = 0; epoch < 100; ++epoch) {
    std::vector<size_t> tileToFlip;
    for (int64_t i = - board.height / 2 + 1; i < board.height / 2 - 1; ++i) {
      for (int64_t j = - board.width / 2; j < board.width / 2 - 1; ++j) {
        const size_t offset = board.offset(j, i);
        const int count = board.countNeighbors(offset);

        if (board(offset) == 1 && (count == 0 || count > 2)) {
          tileToFlip.push_back(offset);
        }
        if (board(offset) == 0 && count == 2) {
          tileToFlip.push_back(offset);
        }
      }
    }
    for (auto address : tileToFlip) {
      board.flip(address);
    }
  }

  size_t part2 = 0;
  for (auto i : board.buffer) {
    part2 += i;
  }

  return {part1, part2};
}

} // namespace day24