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
  int total = 0;
  while (infile >> mass) {
    int fuel = mass / 3 - 2;
    std::cout << "input module mass : " << mass << " -- fuel required : " << fuel << std::endl;
    total += fuel;
  }
  std::cout << "Total : " << total << std::endl;
  return 0;
}
