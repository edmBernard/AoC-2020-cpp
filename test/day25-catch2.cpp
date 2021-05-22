#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day25/day25.hpp"

TEST_CASE("AoC2020 Day25", "[day25]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day25/input_part1_test1.txt", 14897079, 0),
      std::make_tuple("day25/input.txt", 19414467, 0)
    }));

  CAPTURE(filename);

  auto res = day25::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day25::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day25::part2(res) == expectedPart2);
  }
}