#include <fstream>
#include <iostream>

int main(int argc, const char **argv) {
  std::cout << "Input File : " << argv[1] << std::endl;
  std::ifstream infile(argv[1]);
  if (!infile.is_open()) {
    std::cout << "File Not Found" << std::endl;
    return 1;
  }
  int mass;
  int total_fuel = 0;
  while (infile >> mass) {
    do {
      mass = mass / 3 - 2;
    } while (mass > 0 && (total_fuel += mass));
  }

  std::cout << "Total : " << total_fuel << std::endl;
  return 0;
}
