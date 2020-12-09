#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day9/day9.hpp"

TEST_CASE("AoC2020 Day9", "[day9]") {

  auto [filename, preambleSize, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t, size_t>({
      std::make_tuple("day9/input_part1_test1.txt", 5, 127, 62),
      std::make_tuple("day9/input.txt", 25, 675280050, 96081673)
    }));

  auto res = day9::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day9::part1(res, preambleSize) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day9::part2(res, preambleSize) == expectedPart2);
  }
}