#include <iostream>
#include <chrono>
#include <fmt/core.h>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"


int main() {

  double totalCount = 0;
  const int repetition = 1000;

  for (int i = 0; i < repetition; ++i) {
    {
      auto start_temp = std::chrono::high_resolution_clock::now();
      day1::part1(day1::parseInputFile("day1/input.txt"));
      day1::part2(day1::parseInputFile("day1/input.txt"));
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
      fmt::print("day1 : {} ms \n", elapsed_temp.count());
      totalCount += elapsed_temp.count();
    }
    {
      auto start_temp = std::chrono::high_resolution_clock::now();
      day2::part1(day2::parseInputFile("day2/input.txt"));
      day2::part2(day2::parseInputFile("day2/input.txt"));
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
      fmt::print("day2 : {} ms \n", elapsed_temp.count());
      totalCount += elapsed_temp.count();
    }
    {
      auto start_temp = std::chrono::high_resolution_clock::now();
      day3::part1(day3::parseInputFile("day3/input.txt"));
      day3::part2(day3::parseInputFile("day3/input.txt"));
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
      fmt::print("day3 : {} ms \n", elapsed_temp.count());
      totalCount += elapsed_temp.count();
    }
    {
      auto start_temp = std::chrono::high_resolution_clock::now();
      day4::part1(day4::parseInputFile("day4/input.txt"));
      day4::part2(day4::parseInputFile("day4/input.txt"));
      std::chrono::duration<double, std::milli> elapsed_temp = std::chrono::high_resolution_clock::now() - start_temp;
      fmt::print("day4 : {} ms \n", elapsed_temp.count());
      totalCount += elapsed_temp.count();
    }
  }

  fmt::print("Total duration per run : {} ms \n", totalCount / repetition);
  return 0;
}
