
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
int part1(const Map<T> &map, size_t stepX, size_t stepY) {
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

int part2(const std::vector<std::tuple<int, int, char, std::string>> &list) {
  int validPassword = 0;
  for (auto [pos1, pos2, letter, password] : list) {
    if ((password[pos1 - 1] == letter) ^ (password[pos2 - 1] == letter)) {
      ++validPassword;
    }
  }
  return validPassword;
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