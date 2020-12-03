#include <iostream>

#include "day3.hpp"


int main(int argc, const char **argv) {
  using namespace day3;
  std::cout << "Input File : " << argv[1] << std::endl;

  std::cout << "Result part1: " << part1(parseInputFile(argv[1]), 3, 1) << std::endl;
  // std::cout << "Result part2: " << part2(parseInputFile(argv[1])) << std::endl;

  return 0;
}
