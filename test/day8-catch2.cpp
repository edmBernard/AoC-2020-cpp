#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day8/day8.hpp"

TEST_CASE("AoC2020 Day8", "[day8]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, long long>({
      std::make_tuple("day8/input_part1_test1.txt", 5, 8),
      std::make_tuple("day8/input.txt", 1684, 2188)
    }));

  auto res = day8::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day8::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day8::part2(res) == expectedPart2);
  }
}