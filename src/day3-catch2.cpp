#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day3/day3.hpp"

TEST_CASE("AoC2020 Day3", "[day3]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day3/input_part1_test1.txt", 7, 336),
      std::make_tuple("day3/input.txt", 200, 3737923200)
    }));

  day3::Map<short> map = day3::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day3::part1(map) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day3::part2(map) == expectedPart2);
  }
}