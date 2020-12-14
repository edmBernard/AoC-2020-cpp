#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day14/day14.hpp"

TEST_CASE("AoC2020 Day14", "[day14]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day14/input_part1_test1.txt", 165, 404),
      std::make_tuple("day14/input_part1_test2.txt", 51, 208),
      std::make_tuple("day14/input.txt", 11926135976176, 4330547254348)
    }));

  auto res = day14::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day14::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day14::part2(res) == expectedPart2);
  }
}