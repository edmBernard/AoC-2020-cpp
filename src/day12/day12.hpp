
#pragma once

#include <algorithm>
#include <charconv>
#include <exception>
#include <fstream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace day12 {

struct Point {
  int64_t x;
  int64_t y;

  int manhattan() {
    return abs(this->x) + abs(this->y);
  }

  Point operator+(const Point &pt) {
    return {this->x + pt.x, this->y + pt.y};
  }
  Point operator*(const int &value) {
    return {this->x * value, this->y * value};
  }
  Point &operator+=(const Point &pt) {
    this->x += pt.x;
    this->y += pt.y;
    return *this;
  }
  Point &rot(const int &value) {
    switch (value) {
    case 90:
    case -270: {
      int temp = this->y;
      this->y = -this->x;
      this->x = temp;
      break;
    }
    case 180:
    case -180:
      this->x = -this->x;
      this->y = -this->y;
      break;
    case 270:
    case -90: {
      int temp = this->y;
      this->y = this->x;
      this->x = -temp;
      break;
    }
    default:
      throw std::runtime_error("Rotation value Not implemented : " + std::to_string(value));
    }
    return *this;
  }
};

std::ostream &operator<<(std::ostream &os, const Point &pt) {
  return os << "(" << pt.x << "," << pt.y << ")";
}

size_t part1(const std::vector<std::pair<char, int>> &actions) {
  // x = west/east axis
  // y = south/north axis

  Point pos{0, 0};
  Point currentDir{1, 0};

  for (auto [c, v] : actions) {
    switch (c) {
    case 'N':
      pos += Point{0, 1} * v;
      break;
    case 'S':
      pos += Point{0, -1} * v;
      break;
    case 'E':
      pos += Point{1, 0} * v;
      break;
    case 'W':
      pos += Point{-1, 0} * v;
      break;
    case 'R':
      currentDir.rot(v);
      break;
    case 'L':
      currentDir.rot(-v);
      break;
    case 'F':
      pos += currentDir * v;
      break;
    default:
      throw std::runtime_error(std::string("Unrecognize action : ") + c);
    }
  }
  return pos.manhattan();
}

size_t part2(const std::vector<std::pair<char, int>> &actions) {
  // x = west/east axis
  // y = south/north axis

  Point pos{0, 0};
  Point waypoint{10, 1};

  for (auto [c, v] : actions) {
    switch (c) {
    case 'N':
      waypoint += Point{0, 1} * v;
      break;
    case 'S':
      waypoint += Point{0, -1} * v;
      break;
    case 'E':
      waypoint += Point{1, 0} * v;
      break;
    case 'W':
      waypoint += Point{-1, 0} * v;
      break;
    case 'R':
      waypoint.rot(v);
      break;
    case 'L':
      waypoint.rot(-v);
      break;
    case 'F':
      pos += waypoint * v;
      break;
    default:
      throw std::runtime_error(std::string("Unrecognize action : ") + c);
    }
  }
  return pos.manhattan();
}

std::vector<std::pair<char, int>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<std::pair<char, int>> actions;
  std::string line;
  int value;
  while (infile >> line) {
    auto [p, ec] = std::from_chars(line.data() + 1, line.data() + line.size(), value);
    if (ec == std::errc()) {
      actions.push_back({line[0], value});
    } else {
      std::cout << "Debug: failed to parse " << line << std::endl;
    }

  }

  return actions;
}

} // namespace day12