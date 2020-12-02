#include <iostream>

#include "day2.hpp"


int main(int argc, const char **argv) {
  using namespace day2;
  std::cout << "Input File : " << argv[1] << std::endl;


  std::vector<std::tuple<int, int, char, std::string>> elementList = parseInputFile(argv[1]);

  std::cout << "Result part1: " << part1(parseInputFile(argv[1])) << std::endl;
  // std::cout << "Result part2: " << parseInputFile(argv[1]) << std::endl;

  return 0;
}
