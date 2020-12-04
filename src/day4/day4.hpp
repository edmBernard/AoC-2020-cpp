
#pragma once

#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <array>
#include <numeric>


namespace day4 {

template <typename T>
class Map {
public:
  Map(std::vector<T> &buffer, size_t stride, size_t height)
      : buffer(buffer), stride(stride), height(height) {}

  T operator()(size_t x, size_t y) const {
    return buffer[x % stride + y * stride];
  }

  size_t getHeight() const {
    return height;
  }

private:
  size_t height;
  size_t stride;
  std::vector<T> buffer;
};

template <typename T>
int getEncounteredTree(const Map<T> &map, size_t stepX, size_t stepY) {
  int count = 0;
  for (size_t posX = 0, posY = 0; posY < map.getHeight(); posX += stepX, posY += stepY) {
    count += map(posX, posY);
  }
  return count;
}

int part1(const std::vector<std::map<std::string, std::string>> &passportList) {
  int validPassport = 0;
  for (auto pp : passportList) {
    int fieldCount = 0;
    std::map<std::string, int> passportCount;
    for (auto [key, value] : pp) {
      if (key != "cid") {
        ++fieldCount;
      }
    }
    if (fieldCount == 7) {
      ++validPassport;
    }
  }
  return validPassport;
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

std::vector<std::map<std::string, std::string>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::string field;
  std::string key;
  std::string value;

  std::vector<std::map<std::string, std::string>> passportList;
  std::map<std::string, std::string> passport;
  while (getline(infile, line)) {
    std::stringstream ssLine(line);
    if (line.empty()) {
      passportList.push_back(passport);
      passport.clear();
      continue;
    }
    while (std::getline(ssLine, field, ' ')) {
      std::stringstream ssField(field);

      std::getline(ssField, key, ':');
      std::getline(ssField, value);

      passport[key] = value;
    }
  }
  passportList.push_back(passport);  // the last passport was not push by new line

  return passportList;
}

} // namespace day3