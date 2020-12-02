
#pragma once

#include <exception>
#include <fstream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

namespace day2 {

int countLetter(std::string input, char letter) {
  int res = 0;
  for (auto i : input) {
    if (i == letter) {
      ++res;
    }
  }
  return res;
}

int part1(const std::vector<std::tuple<int, int, char, std::string>> &list) {
  int validPassword = 0;
  for (auto [min, max, letter, password] : list) {
    if (int count = countLetter(password, letter); count >= min && count <= max) {
      ++validPassword;
    }
  }
  return validPassword;
}


std::vector<std::tuple<int, int, char, std::string>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<std::tuple<int, int, char, std::string>> elementList;
  std::string line;
  std::regex parseRegex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
  std::smatch match;
  while (getline(infile, line)) {
    if (std::regex_match(line, match, parseRegex); match.size() == 5) {
      elementList.push_back(std::make_tuple(std::stoi(match[1]), std::stoi(match[2]), match[3].str()[0], match[4].str()));
    }
  }
  return elementList;
}

} // namespace day2