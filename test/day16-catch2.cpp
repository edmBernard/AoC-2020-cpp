#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day16/day16.hpp"

TEST_CASE("AoC2020 Day16", "[day16]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day16/input_part1_test1.txt", 71, 1),
      std::make_tuple("day16/input_part2_test1.txt", 0, 12),
      std::make_tuple("day16/input.txt", 21081, 314360510573)
    }));

  auto res = day16::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day16::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day16::part2(res) == expectedPart2);
  }
}