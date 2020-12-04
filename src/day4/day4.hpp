
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

int part2(const std::vector<std::map<std::string, std::string>> &passportList) {
  int validPassport = 0;
  for (auto pp : passportList) {
    int fieldCount = 0;
    for (const auto &[key, value] : pp) {
      if (key == "byr") {
        // byr (Birth Year) - four digits; at least 1920 and at most 2002.
        if (int date = std::stoi(value); date >= 1920 && date <= 2002) {
          ++fieldCount;
        }
        continue;
      }
      if (key == "iyr") {
        // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
        if (int date = std::stoi(value); date >= 2010 && date <= 2020) {
          ++fieldCount;
        }
        continue;
      }
      if (key == "eyr") {
        // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
        if (int date = std::stoi(value); date >= 2020 && date <= 2030) {
          ++fieldCount;
        }
        continue;
      }
      if (key == "hgt") {
        // hgt (Height) - a number followed by either cm or in:
        // If cm, the number must be at least 150 and at most 193.
        // If in, the number must be at least 59 and at most 76.

#ifdef USE_OPTIMIZED_VERSION
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
#else
        const std::regex parseRegex("([0-9]+)(in|cm)");
        std::smatch match;
        if (std::regex_match(value, match, parseRegex) && match.size() == 3) {
          const int height = std::stoi(match[1]);
          const std::string unit = match[2].str();
          if (unit == "in" && height >= 59 && height <= 76) {
            ++fieldCount;
          } else if (unit == "cm" && height >= 150 && height <= 193) {
            ++fieldCount;
          }
        }
#endif
        continue;
      }
      if (key == "hcl") {
        // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
        if (value.size() == 7 && value[0] == '#') {
          const std::set<char> validChar = {'#', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
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
        continue;
      }
      if (key == "ecl") {
        // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
        const std::set<std::string> eyeColor = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        if (eyeColor.count(value)) {
          ++fieldCount;
        }
        continue;
      }
      if (key == "pid") {
#ifdef USE_OPTIMIZED_VERSION
        long long pid;
        auto [p, ec] = std::from_chars(value.data(), value.data() + value.size(), pid);
        if (ec == std::errc() && pid > 0 && value.size() == 9) {
          ++fieldCount;
        }
#else
        try {
          if (long long id = std::stoll(value); id > 0 && value.size() == 9) {
            ++fieldCount;
          }
        } catch (const std::invalid_argument &) {
        }
#endif
        continue;
      }
      if (key == "cid") {
        // cid (Country ID) - ignored, missing or not.
      }
    }
    if (fieldCount == 7) {
      ++validPassport;
    }
  }
  return validPassport;
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
  passportList.push_back(passport); // the last passport was not push by new line

  return passportList;
}

} // namespace day4