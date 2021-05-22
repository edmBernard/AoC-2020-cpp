#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day24/day24.hpp"

TEST_CASE("AoC2020 Day24", "[day24]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day24/input_part1_test1.txt", 10, 2208),
      std::make_tuple("day24/input.txt", 391, 3876)
    }));

  CAPTURE(filename);

  auto res = day24::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day24::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day24::part2(res) == expectedPart2);
  }
}