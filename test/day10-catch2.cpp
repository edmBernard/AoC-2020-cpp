#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day10/day10.hpp"

TEST_CASE("AoC2020 Day10", "[day10]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day10/input_part1_test1.txt", 35, 8),
      std::make_tuple("day10/input_part1_test2.txt", 220, 19208),
      std::make_tuple("day10/input_part1_test3.txt", 7, 44),
      std::make_tuple("day10/input.txt", 2343, 31581162962944)
    }));

  auto res = day10::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day10::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day10::part2(res) == expectedPart2);
  }
}