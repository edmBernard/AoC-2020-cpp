#include <iostream>

#include "day1.hpp"


int main(int argc, const char **argv) {
  std::cout << "Input File : " << argv[1] << std::endl;

  std::cout << "Result part1: " << find2Sum(parseInputFile(argv[1])) << std::endl;
  std::cout << "Result part2: " << find3Sum(parseInputFile(argv[1])) << std::endl;

  return 0;
}
