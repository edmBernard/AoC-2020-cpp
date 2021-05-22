
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

namespace day24 {



size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}

size_t loop(size_t value, size_t subjectNumber) {
  value *= subjectNumber;
  value %= 20201227;
  return value;
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

  std::vector<Point> getNeighbors() const {
    std::vector<Point> neighbors;
    neighbors.reserve(6);
    neighbors.emplace_back(x + 1, y + 0);
    neighbors.emplace_back(x - 1, y + 0);
    neighbors.emplace_back(x + 0, y + 1);
    neighbors.emplace_back(x + 0, y - 1);
    neighbors.emplace_back(x + 1, y - 1);
    neighbors.emplace_back(x - 1, y + 1);
    return neighbors;
  }
};

void flipTile(std::map<Point, bool> &list, Point pt) {
  bool &color = list[pt];
  if (list.contains(pt)) {
    color = !color;
  } else {
    color = true;
  }

  if (color) {
    for (auto neighbor : pt.getNeighbors()) {
      if (!list.contains(neighbor)) {
        list[neighbor] = false;
      }
    }
  }
}

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;

  std::map<Point, bool> listOfFlippedTile;

  while (getline(infile, line)) {
    Point pt{0, 0};
    for (int i = 0; i < line.length();) {
      i += pt.move(line.substr(i));
    }
    flipTile(listOfFlippedTile, pt);
  }

  size_t part1 = 0;
  for (auto [_, color] : listOfFlippedTile) {
    part1 += color;
  }

  for (int epoch = 0; epoch < 100; ++epoch) {
    std::vector<Point> tileToFlip;
    for (auto [tile, color] : listOfFlippedTile) {
      int count = 0;
      for (const Point &neighbor : tile.getNeighbors()) {
        if (listOfFlippedTile.contains(neighbor)) {
          if (listOfFlippedTile[neighbor]) {
            ++count;
          }
        }
      }

      if (color && (count == 0 || count > 2)) {
        tileToFlip.push_back(tile);
      }
      if (!color && count == 2) {
        tileToFlip.push_back(tile);
      }
    }

    for (auto tile : tileToFlip) {
      flipTile(listOfFlippedTile, tile);
    }
  }

  size_t part2 = 0;
  for (auto [_, color] : listOfFlippedTile) {
    part2 += color;
  }
  return {part1, part2};
}

} // namespace day24