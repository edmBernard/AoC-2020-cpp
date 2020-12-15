#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day15/day15.hpp"

TEST_CASE("AoC2020 Day15", "[day15]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day15/input_part1_test1.txt", 436, 175594),
      std::make_tuple("day15/input.txt", 412, 243)
    }));

  auto res = day15::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day15::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day15::part2(res) == expectedPart2);
  }
}