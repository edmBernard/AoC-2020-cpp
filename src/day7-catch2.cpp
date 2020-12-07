#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day6/day6.hpp"

TEST_CASE("AoC2020 Day6", "[day6]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, long long>({
      std::make_tuple("day6/input_part1_test1.txt", 4, 6),
      std::make_tuple("day6/input.txt", 233, 3512)
    }));

  auto res = day6::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day6::part1(res) == expectedPart1);
  }
  // SECTION("Part2 : " + filename) {
  //   CHECK(day6::part2(res) == expectedPart2);
  // }
}