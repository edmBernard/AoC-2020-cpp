
#pragma once

#include <vector>
#include <string>
#include <exception>
#include <fstream>


size_t find2Sum(const std::vector<size_t>& list) {
  for (auto l1 : list) {
    for (auto l2 : list) {
      if (l1 + l2 == 2020) {
        return l1 * l2;
      }
    }
  }
  return 0;
}

size_t find3Sum(const std::vector<size_t>& list) {
  for (auto l1 : list) {
    for (auto l2 : list) {
      for (auto l3 : list) {
        if (l1 + l2 + l3 == 2020) {
          return l1 * l2 * l3;
        }
      }
    }
  }
  return 0;
}

std::vector<size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<size_t> numberList;
  std::string line;
  while (infile >> line) {
    numberList.push_back(std::stoi(line));
  }
  return numberList;
}