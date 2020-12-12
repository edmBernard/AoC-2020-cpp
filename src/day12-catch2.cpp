#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day12/day12.hpp"

TEST_CASE("AoC2020 Day12", "[day12]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day12/input_part1_test1.txt", 25, 286),
      std::make_tuple("day12/input.txt", 2847, 29839)
    }));

  auto res = day12::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day12::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day12::part2(res) == expectedPart2);
  }
}