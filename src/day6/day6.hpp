
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

namespace day6 {


int part1(const std::vector<std::array<int, 27>> &answerList) {
  int count = 0;
  for (const auto& answer : answerList) {
    count -= 1;
    for (const auto & letter : answer) {
      count += letter > 0;
    }
  }
  return count;
}


int part2(const std::vector<std::array<int, 27>> &answerList) {
  int count = 0;

  for (const auto& answer : answerList) {
    int numberPeople = answer[0];
    count -= 1; // to remove first letter that represente number of people in the group
    for (const auto & letter : answer) {
      if(letter == numberPeople) {
        count += 1;
      }
    }
  }
  return count;
}


std::vector<std::array<int, 27>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;
  std::string field;
  std::string key;
  std::string value;

  std::vector<std::array<int, 27>> answerList;

  std::array<int, 27> answer;
  answer.fill(0);

  while (getline(infile, line)) {
    if (line.empty()) {
      answerList.push_back(answer);
      answer.fill(0);
      continue;
    }
    for (char c : line) {
      answer[c - 'a' + 1] += 1;
    }
    answer[0] += 1;
  }
  answerList.push_back(answer);  // the last passport was not push by new line
  return answerList;
}


} // namespace day6