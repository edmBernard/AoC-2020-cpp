
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

namespace day7 {


int part1(const std::map<std::string, std::string> &dependencyGraph) {
  int count = 0;

  return count;
}


int part2(const std::vector<std::array<int, 27>> &answerList) {
  int count = 0;

  return count;
}


std::map<std::string, std::string> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;

  std::regex regexFullLine("(.*) contain(.*)$");
  std::regex regexContainedBag(" ([0-9]+) ([^0-9.,]+)[.,]");
  std::smatch matchContainer;
  std::smatch matchContained;
  std::multimap<std::string, std::string> dependencyGraph;
  while (getline(infile, line)) {
    std::cout << "new line : " << std::endl;
    if (std::regex_match(line, matchContainer, regexFullLine)) {

      const auto words_begin = std::sregex_iterator(line.begin(), line.end(), regexContainedBag);
      const auto words_end = std::sregex_iterator();

      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
          matchContained = *i;
          for (int i = 1; i < matchContained.size(); ++i) {
            dependencyGraph.insert({matchContained[2].str(), matchContainer[1].str()});
          }
      }

    }
  }
  for (auto & e : dependencyGraph) {
    std::cout << "{" << e.first << "->" << e.second << "} ";
  }
  return {};
}


} // namespace day7