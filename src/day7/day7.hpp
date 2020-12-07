
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

void findUpperContainer(std::set<std::string> &output, std::string search, const std::multimap<std::string, std::string> &dependencyGraph) {
  auto range = dependencyGraph.equal_range(search);
  for (auto it = range.first; it != range.second; ++it){
    if (!output.count(it->second)) {
      output.insert(it->second);
      findUpperContainer(output, it->second, dependencyGraph);
    }
  }
}

int part1(const std::multimap<std::string, std::string> &dependencyGraph) {
  std::set<std::string> res;
  findUpperContainer(res, "shiny gold", dependencyGraph);
  return res.size();
}


int part2(const std::multimap<std::string, std::string> &answerList) {
  int count = 0;

  return count;
}


std::multimap<std::string, std::string> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;

  std::regex regexFullLine("(.*) bags contain(.*)$");
  std::regex regexContainedBag(" ([0-9]+) ([^0-9.,]+) bags?[.,]");
  std::smatch matchContainer;
  std::smatch matchContained;
  std::multimap<std::string, std::string> dependencyGraph;
  while (getline(infile, line)) {
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
  return dependencyGraph;
}


} // namespace day7