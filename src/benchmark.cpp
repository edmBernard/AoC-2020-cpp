#include <chrono>
#include <fmt/core.h>
#include <iostream>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"
#include "day5/day5.hpp"
#include "day6/day6.hpp"
#include "day7/day7.hpp"
#include "day8/day8.hpp"
#include "day9/day9.hpp"
#include "day10/day10.hpp"
#include "day11/day11.hpp"
#include "day12/day12.hpp"
#include "day13/day13.hpp"
#include "day14/day14.hpp"
#include "day15/day15.hpp"
#include "day16/day16.hpp"
#include "day17/day17.hpp"
#include "day18/day18.hpp"
#include "day19/day19.hpp"
#include "day23/day23.hpp"
#include "day24/day24.hpp"
#include "day25/day25.hpp"

// Temporary until I find a nicer solution without macro :(
#define BENCH_SPLIT(x)                                                                                                 \
  {                                                                                                                    \
    double time_day##x = 0;                                                                                            \
    for (int i = 0; i < repetition; ++i) {                                                                             \
      auto start_temp = std::chrono::high_resolution_clock::now();                                                     \
      auto res = day##x::parseInputFile("day" + std::to_string(x) + "/input.txt");                                     \
      day##x::part1(res);                                                                                              \
      day##x::part2(res);                                                                                              \
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp; \
      time_day##x += elapsed_temp.count();                                                                             \
    }                                                                                                                  \
    totalCount += time_day##x;                                                                                         \
    fmt::print("Day{: <5} : {:.2f} ms \n", x, time_day##x / repetition);                                           \
  }

#define BENCH(x)                                                                                                       \
  {                                                                                                                    \
    double time_day##x = 0;                                                                                            \
    for (int i = 0; i < repetition; ++i) {                                                                             \
      auto start_temp = std::chrono::high_resolution_clock::now();                                                     \
      auto [part1, part2] = day##x::allInOne("day" + std::to_string(x) + "/input.txt");                                \
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp; \
      time_day##x += elapsed_temp.count();                                                                             \
    }                                                                                                                  \
    totalCount += time_day##x;                                                                                         \
    fmt::print("Day{} AllInOne: {:.2f} ms \n", x, time_day##x / repetition);                                           \
  }

int main() {

  double totalCount = 0;

  const int repetition = 10;
  BENCH_SPLIT(1);
  BENCH_SPLIT(2);
  BENCH_SPLIT(3);
  BENCH_SPLIT(4);
  BENCH_SPLIT(5);
  BENCH_SPLIT(6);
  BENCH_SPLIT(7);
  BENCH_SPLIT(8);
  BENCH_SPLIT(9);
  BENCH_SPLIT(10);
  BENCH_SPLIT(11);
  BENCH_SPLIT(12);
  BENCH_SPLIT(13);
  BENCH_SPLIT(14);
  BENCH_SPLIT(15);
  BENCH_SPLIT(16);
  BENCH_SPLIT(17);
  BENCH_SPLIT(18);
  BENCH_SPLIT(19);
  BENCH_SPLIT(23);
  BENCH_SPLIT(24);
  BENCH_SPLIT(25);

  fmt::print("Total duration per run : {:.2f} ms \n\n", totalCount / repetition);

  BENCH(4);

  return 0;
}
