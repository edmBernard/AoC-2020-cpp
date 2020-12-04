#include <chrono>
#include <fmt/core.h>
#include <iostream>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"

// Temporary until I find a nicer solution without macro :(
#define BENCH(x)                                                                                                     \
  double day##x = 0;                                                                                            \
  for (int i = 0; i < repetition; ++i) {                                                                             \
    auto start_temp = std::chrono::high_resolution_clock::now();                                                     \
    day##x::part1(day##x::parseInputFile("day" + std::to_string(x) + "/input.txt"));                                 \
    day##x::part2(day##x::parseInputFile("day" + std::to_string(x) + "/input.txt"));                                 \
    std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp; \
    day##x += elapsed_temp.count();                                                                                  \
  }                                                                                                                  \
  totalCount += day##x;                                                                                              \
  fmt::print("day{} : {:.2f} ms \n", x, day##x / repetition);

int main() {

  double totalCount = 0;
  const int repetition = 1000;

  BENCH(1);
  BENCH(2);
  BENCH(3);
  BENCH(4);

  fmt::print("Total duration per run : {:.2f} ms \n", totalCount / repetition);

  return 0;
}
