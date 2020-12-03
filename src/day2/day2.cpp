#include <iostream>

#include "day2.hpp"


int main(int, const char **argv) {
  using namespace day2;
  std::cout << "Input File : " << argv[1] << std::endl;

  std::cout << "Result part1: " << part1(parseInputFile(argv[1])) << std::endl;
  std::cout << "Result part2: " << part2(parseInputFile(argv[1])) << std::endl;

  return 0;
}
