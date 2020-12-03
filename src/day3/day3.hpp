
#pragma once

#include <exception>
#include <fstream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

namespace day3 {

template <typename T>
class Map {
public:
  Map(std::vector<T> &buffer, size_t stride, size_t height)
      : buffer(buffer), stride(stride), height(height) {}

  T operator()(size_t x, size_t y) const {
    return buffer[x % stride + y * stride];
  }

  size_t stride;
  size_t height;

private:
  std::vector<T> buffer;
};

template <typename T>
int getEncounteredTree(const Map<T> &map, size_t stepX, size_t stepY) {
  int count = 0;
  size_t posX = 0;
  size_t posY = 0;
  while (posY < map.height) {
    count += map(posX, posY);
    posX += stepX;
    posY += stepY;
  }
  return count;
}

int part1(const Map<short> &map) {
  return getEncounteredTree(map, 3, 1);
}

long long part2(const Map<short> &map) {
  std::vector<std::pair<size_t, size_t>> listSlope = {
    {1, 1},
    {3, 1},
    {5, 1},
    {7, 1},
    {1, 2}};

  long long res = 1;
  for (auto [stepX, stepY] : listSlope) {
    res *= getEncounteredTree(map, stepX, stepY);
  }

  return res;
}



Map<short> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<short> buffer;
  std::string line;
  size_t stride = 0;
  size_t height = 0;

  while (getline(infile, line)) {
    ++height;
    for (auto i : line) {
      if (i == '#') {
        buffer.push_back(1);
      } else {
        buffer.push_back(0);
      }
      stride = line.size();
    }
  }
  return Map(buffer, stride, height);
}

} // namespace day3