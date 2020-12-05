
#pragma once

#include <algorithm>
#include <array>
#include <charconv>
#include <exception>
#include <fstream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace day4 {

enum FIELD {
  BYR = 1,
  IYR = 1 << 1,
  EYR = 1 << 2,
  HGT = 1 << 3,
  HCL = 1 << 4,
  ECL = 1 << 5,
  PID = 1 << 6,
  CID = 1 << 7
};

bool haveAllField(int flag) {
  return (flag | FIELD::CID) == 255.;
}

bool haveAllFieldValid(int flag, const std::array<std::string, 8> &content) {
  int fieldCount = 0;
  if (flag & FIELD::BYR) {
    // byr (Birth Year) - four digits; at least 1920 and at most 2002.
    if (int date = std::stoi(content[0]); date >= 1920 && date <= 2002) {
      ++fieldCount;
    }
  }
  if (flag & FIELD::IYR) {
    // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    if (int date = std::stoi(content[1]); date >= 2010 && date <= 2020) {
      ++fieldCount;
    }
  }
  if (flag & FIELD::EYR) {
    // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    if (int date = std::stoi(content[2]); date >= 2020 && date <= 2030) {
      ++fieldCount;
    }
  }
  if (flag & FIELD::HGT) {
    // hgt (Height) - a number followed by either cm or in:
    // If cm, the number must be at least 150 and at most 193.
    // If in, the number must be at least 59 and at most 76.
    const std::string_view value = content[3];
    const char lastChar = value[value.size() - 1];
    if (lastChar == 'n') {
      int height;
      auto [p, ec] = std::from_chars(value.data(), value.data() + value.size() - 2, height);
      if (ec == std::errc() && height >= 59 && height <= 76) {
        ++fieldCount;
      }
    } else if (lastChar == 'm') {
      int height;
      auto [p, ec] = std::from_chars(value.data(), value.data() + value.size() - 2, height);
      if (ec == std::errc() && height >= 150 && height <= 193) {
        ++fieldCount;
      }
    }
  }
  if (flag & FIELD::HCL) {
    // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    const std::string_view value = content[4];
    if (value.size() == 7 && value[0] == '#') {
      static const std::set<char> validChar = {'#', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
      bool hasInvalidChar = false;
      for (char c : value) {
        if (!validChar.count(c)) {
          hasInvalidChar = true;
        }
      }
      if (!hasInvalidChar) {
        ++fieldCount;
      }
    }
  }
  if (flag & FIELD::ECL) {
    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    static const std::set<std::string> eyeColor = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    if (eyeColor.count(content[5])) {
      ++fieldCount;
    }
  }
  if (flag & FIELD::PID) {
    // (Passport ID) - a nine-digit number, including leading zeroes.
    const std::string_view value = content[6];
    long long pid;
    auto [p, ec] = std::from_chars(value.data(), value.data() + value.size(), pid);
    if (ec == std::errc() && pid > 0 && value.size() == 9) {
      ++fieldCount;
    }
  }
  if (flag & FIELD::CID) {
    // cid (Country ID) - ignored, missing or not.
  }
  return fieldCount == 7;
}

int part1(const std::tuple<int, int> &result) {
  return std::get<0>(result);
}
int part2(const std::tuple<int, int> &result) {
  return std::get<1>(result);
}

std::tuple<int, int> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::string field;
  std::string key;
  std::string value;

  int part1 = 0;
  int part2 = 0;

  int flag = 0;
  std::array<std::string, 8> fieldContent;

  while (getline(infile, line)) {
    std::stringstream ssLine(line);
    if (line.empty()) {
      if (haveAllField(flag)) {
        ++part1;
        if (haveAllFieldValid(flag, fieldContent)) {
          ++part2;
        }
      }
      flag = 0;
      continue;
    }
    while (std::getline(ssLine, field, ' ')) {
      std::stringstream ssField(field);

      std::getline(ssField, key, ':');
      std::getline(ssField, value);

      if (key == "byr") {
        flag |= FIELD::BYR;
        fieldContent[0] = value;
      } else if (key == "iyr") {
        flag |= FIELD::IYR;
        fieldContent[1] = value;
      } else if (key == "eyr") {
        flag |= FIELD::EYR;
        fieldContent[2] = value;
      } else if (key == "hgt") {
        flag |= FIELD::HGT;
        fieldContent[3] = value;
      } else if (key == "hcl") {
        flag |= FIELD::HCL;
        fieldContent[4] = value;
      } else if (key == "ecl") {
        flag |= FIELD::ECL;
        fieldContent[5] = value;
      } else if (key == "pid") {
        flag |= FIELD::PID;
        fieldContent[6] = value;
      } else if (key == "cid") {
        flag |= FIELD::CID;
        fieldContent[7] = value;
      }
    }
  }
  if (haveAllField(flag)) {
    ++part1;
    if (haveAllFieldValid(flag, fieldContent)) {
      ++part2;
    }
  }

  return {part1, part2};
}

} // namespace day4