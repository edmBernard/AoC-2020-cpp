#include <iostream>

#include "day15.hpp"


int main(int, const char **argv) try {
  using namespace day15;
  std::cout << "Input File : " << argv[1] << std::endl;

  std::cout << "Result part1: " << part1(parseInputFile(argv[1])) << std::endl;
  std::cout << "Result part2: " << part2(parseInputFile(argv[1])) << std::endl;

  return 0;

} catch (const std::exception &e) {
  std::cerr << "Exception: " << e.what() << std::endl;
}
