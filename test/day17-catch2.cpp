#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day17/day17.hpp"

TEST_CASE("AoC2020 Day17", "[day17]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day17/input_part1_test1.txt", 112, 848),
      std::make_tuple("day17/input.txt", 336, 2620)
    }));

  auto res = day17::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day17::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day17::part2(res) == expectedPart2);
  }
}