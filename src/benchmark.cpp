#include <iostream>
#include <chrono>
#include <fmt/core.h>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"


int main() {

  double totalCount = 0;
  {
    auto start_temp = std::chrono::high_resolution_clock::now();
    day1::part1(day1::parseInputFile("input/day1/input.txt"));
    std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
    fmt::print("day1 : {} ms \n", elapsed_temp.count());
    totalCount += elapsed_temp.count();
  }
  {
    auto start_temp = std::chrono::high_resolution_clock::now();
    day2::part1(day2::parseInputFile("input/day2/input.txt"));
    std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
    fmt::print("day2 : {} ms \n", elapsed_temp.count());
    totalCount += elapsed_temp.count();
  }
  {
    auto start_temp = std::chrono::high_resolution_clock::now();
    day3::part1(day3::parseInputFile("input/day3/input.txt"));
    std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
    fmt::print("day3 : {} ms \n", elapsed_temp.count());
    totalCount += elapsed_temp.count();
  }

  fmt::print("Total duration : {} ms \n", totalCount);
  return 0;
}
