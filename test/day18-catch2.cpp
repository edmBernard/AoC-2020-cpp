#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day18/day18.hpp"

TEST_CASE("AoC2020 Day18", "[day18]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day18/input_part1_test1.txt", 71, 0),
      std::make_tuple("day18/input_part1_test2.txt", 276, 0),
      std::make_tuple("day18/input.txt", 9581541, 0)
    }));

  auto res = day18::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day18::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day18::part2(res) == expectedPart2);
  }
}