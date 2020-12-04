
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

int part1(int count) {
  return count;
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

// std::vector<std::map<std::string, std::string>> parseInputFile(std::string filename) {
int parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<short> buffer;
  std::string line;
  std::string field;
  std::string key;
  std::string value;

  std::vector<std::string> fieldList{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
  std::array<int, 8> foundField{{0,0,0,0,0,0,0, 1}};

  int count = 0;
  while (getline(infile, line)) {
    std::stringstream ssLine(line);
    if (line.empty()) {
      foundField = {0,0,0,0,0,0,0, 1};
      continue;
    }
    while (std::getline(ssLine, field, ' ')) {
      std::stringstream ssField(field);

      std::getline(ssField, key, ':');
      std::getline(ssField, value);
      // std::cout << "key: " << key << std::endl;
      // std::cout << "value: " << value << std::endl;

      for (size_t index = 0; index < fieldList.size(); ++index) {
        if (fieldList[index] == key) {
          foundField[index] = 1;
        }
      }
      // std::cout << foundField[0] << foundField[1] << foundField[2] << foundField[3] << foundField[4] << foundField[5] << foundField[6] << foundField[7] << std::endl;
    }

    int sum = 0;
    sum = std::accumulate(foundField.begin() , foundField.end(), sum);
    // std::cout << "sum: " << sum << std::endl;
    if (sum == 8) {
      count += 1;
      foundField = {0,0,0,0,0,0,0, 1};
    }
  }
  return count;
}

} // namespace day3