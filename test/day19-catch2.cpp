#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day19/day19.hpp"

TEST_CASE("AoC2020 Day19", "[day19]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day19/input_part1_test1.txt", 1, 0),
      std::make_tuple("day19/input_part1_test2.txt", 2, 0),
      std::make_tuple("day19/input_part1_test3.txt", 3, 0),
      std::make_tuple("day19/input.txt", 144, 0)
    }));

  CAPTURE(filename);

  auto res = day19::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day19::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day19::part2(res) == expectedPart2);
  }
}