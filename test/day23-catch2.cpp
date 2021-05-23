#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day23/day23.hpp"

TEST_CASE("AoC2020 Day23", "[day23]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day23/input_part1_test1.txt", 67384529, 0),
      std::make_tuple("day23/input.txt", 47598263, 0)
    }));

  CAPTURE(filename);

  auto res = day23::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day23::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day23::part2(res) == expectedPart2);
  }
}