#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day11/day11.hpp"

TEST_CASE("AoC2020 Day11", "[day11]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day11/input_part1_test1.txt", 37, 26),
      std::make_tuple("day11/input.txt", 2470, 2259)
    }));

  auto res = day11::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day11::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day11::part2(res) == expectedPart2);
  }
}