
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

int part1(const std::tuple<std::multimap<std::string, std::string>, std::multimap<std::string, std::pair<int, std::string>>> &dependencyGraph) {
  std::set<std::string> res;
  findUpperContainer(res, "shiny gold", std::get<0>(dependencyGraph));
  return int(res.size());
}

int findDownContainer(std::string search, const std::multimap<std::string, std::pair<int, std::string>> &dependencyGraph) {
  if (search.empty()) {
    return 0;
  }
  auto range = dependencyGraph.equal_range(search);
  int count = 1;
  for (auto it = range.first; it != range.second; ++it){
    count += it->second.first * findDownContainer(it->second.second, dependencyGraph);
  }

  return count;
}

int part2(const std::tuple<std::multimap<std::string, std::string>, std::multimap<std::string, std::pair<int, std::string>>> &dependencyGraph) {
  return findDownContainer("shiny gold", std::get<1>(dependencyGraph)) - 1; // Remove the shiny gold bag
}


std::tuple<std::multimap<std::string, std::string>, std::multimap<std::string, std::pair<int, std::string>>> parseInputFile(std::string filename) {
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
  std::multimap<std::string, std::pair<int, std::string>> dependencyGraph2;
  while (getline(infile, line)) {
    if (std::regex_match(line, matchContainer, regexFullLine)) {

      const auto words_begin = std::sregex_iterator(line.begin(), line.end(), regexContainedBag);
      const auto words_end = std::sregex_iterator();
      if (words_begin == words_end) {
        dependencyGraph2.insert({matchContainer[1].str(), {1, ""}});
      }
      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
          matchContained = *i;
          dependencyGraph.insert({matchContained[2].str(), matchContainer[1].str()});
          dependencyGraph2.insert({matchContainer[1].str(), {std::stoi(matchContained[1].str()), matchContained[2].str()}});
      }

    }
  }

  return {dependencyGraph, dependencyGraph2};
}


} // namespace day7