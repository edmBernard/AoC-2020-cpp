#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int find2Sum(const std::vector<int>& list) {
  for (auto l1 : list) {
    for (auto l2 : list) {
      if (l1 + l2 == 2020) {
        return l1 * l2;
      }
    }
  }
  return 0;
}

int find3Sum(const std::vector<int>& list) {
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

int main(int argc, const char **argv) {
  std::cout << "Input File : " << argv[1] << std::endl;
  std::ifstream infile(argv[1]);
  if (!infile.is_open()) {
    std::cout << "File Not Found" << std::endl;
    return 1;
  }

  std::vector<int> numberList;
  std::string line;
  while (infile >> line) {
    numberList.push_back(std::stoi(line));
  }

  std::cout << "Result part1: " << find2Sum(numberList) << std::endl;
  std::cout << "Result part2: " << find3Sum(numberList) << std::endl;

  return 0;
}
