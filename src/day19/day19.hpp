
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <regex>

namespace day19 {

struct Rule;

std::map<int, std::unique_ptr<Rule>> g_ruleList;


struct Rule {
  Rule(char letter) : letter(letter), isRoot(true) {}
  Rule(std::vector<int> group1, std::vector<int> group2 = {}) : group1(group1), group2(group2), isRoot(false) {}

  bool call(std::string_view s, int& offset) {
    if (isRoot) {
      ++offset;
      return s[0] == letter;

    } else {
      bool match = true;
      int temp_offset = 0;
      for (auto &r : group1) {
        match &= g_ruleList[r]->call(s.data()+temp_offset, temp_offset);
        if (!match) {
          break;
        }
      }

      if (!group2.empty() && match == false) {
        match = true;
        temp_offset = 0;
        for (auto &r : group2) {
          match &= g_ruleList[r]->call(s.data()+temp_offset, temp_offset);
          if (!match) {
            break;
          }
        }
      }

      offset += temp_offset;
      return match;
    }
  }

  void show() {
    if (isRoot) {
      std::cout << "letter: " << letter << std::endl;
    } else {
      std::cout << "group: ";
      for (auto i : group1) {
        std::cout << i << " ";
      }
      std::cout << " | ";
      for (auto i : group2) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
    }
  }

  bool isRoot;
  char letter;
  std::vector<int> group1;
  std::vector<int> group2;
};

size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}

std::vector<int> parseListOfRule(std::string s) {
  std::stringstream ss(s);
  std::string ruleIndex;
  std::vector<int> ruleList;
  while (std::getline(ss, ruleIndex, ' ')) {
    if (!ruleIndex.empty()) {
      ruleList.push_back(std::stoi(ruleIndex));
    }
  }
  return ruleList;
}


std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;
  size_t part1 = 0;
  size_t part2 = 0;
  bool parsingRule = true;

  std::regex rulesRootRegex("([0-9]+): \"([a-z])\"");
  std::regex rulesRegex("([0-9]+): \"([a-z])\"");
  while (getline(infile, line)) {
    if (line.empty()) {
      parsingRule = false;
      continue;
    }

    if (parsingRule) {

      if (std::size_t found = line.find("|"); found != std::string::npos) {
        std::stringstream ss(line);
        std::string ruleIndex;
        std::getline(ss, ruleIndex, ':');
        std::string ruleList1;
        std::getline(ss, ruleList1, '|');
        std::string ruleList2;
        std::getline(ss, ruleList2);

        g_ruleList[std::stoi(ruleIndex)] = std::make_unique<Rule>(parseListOfRule(ruleList1), parseListOfRule(ruleList2));

      } else if (std::size_t found = line.find("\""); found != std::string::npos) {
        std::stringstream ss(line);
        std::string ruleIndex;
        std::getline(ss, ruleIndex, ':');
        g_ruleList[std::stoi(ruleIndex)] = std::make_unique<Rule>(line[found+1]);
      } else {
        std::stringstream ss(line);
        std::string ruleIndex;
        std::getline(ss, ruleIndex, ':');
        std::string ruleList1;
        std::getline(ss, ruleList1);

        g_ruleList[std::stoi(ruleIndex)] = std::make_unique<Rule>(parseListOfRule(ruleList1));

      }

    } else  {
      int offset = 0;
      if (g_ruleList[0]->call(line, offset) && (offset == line.length())) {
        ++part1;
      }
    }
  }

  return {part1, part2};
}

} // namespace day19