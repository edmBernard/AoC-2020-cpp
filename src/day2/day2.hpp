
#pragma once

#include <exception>
#include <fstream>
#include <regex>
#include <sstream>
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

int part2(const std::vector<std::tuple<int, int, char, std::string>> &list) {
  int validPassword = 0;
  for (auto [pos1, pos2, letter, password] : list) {
    if ((password[pos1-1] == letter) ^ (password[pos2-1] == letter)) {
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

#ifdef USE_OPTIMIZED_VERSION
  std::string pos1;
  std::string pos2;
  std::string letter;
  std::string password;
  while (getline(infile, line)) {
    std::stringstream ss(line);
    // example of line content:
    // 1-3 a: abcde
    std::getline(ss, pos1, '-');
    std::getline(ss, pos2, ' ');
    std::getline(ss, letter, ':');
    std::getline(ss, password, ' '); // strip extra white space
    std::getline(ss, password);
    elementList.push_back(std::make_tuple(std::stoi(pos1), std::stoi(pos2), letter[0], password));
  }
#else
  std::regex parseRegex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");
  std::smatch match;
  while (getline(infile, line)) {
    if (std::regex_match(line, match, parseRegex); match.size() == 5) {
      elementList.push_back(std::make_tuple(std::stoi(match[1]), std::stoi(match[2]), match[3].str()[0], match[4].str()));
    }
  }
#endif
  return elementList;
}

} // namespace day2