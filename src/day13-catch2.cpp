#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day13/day13.hpp"

TEST_CASE("AoC2020 Day13", "[day13]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day13/input_part1_test1.txt", 925, 1068781),
      std::make_tuple("day13/input_part1_test1.txt", 47, 1202161486),
      std::make_tuple("day13/input.txt", 2947, 29839)
    }));

  auto res = day13::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day13::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day13::part2(res) == expectedPart2);
  }
}