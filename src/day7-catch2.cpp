#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day7/day7.hpp"

TEST_CASE("AoC2020 Day7", "[day7]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, long long>({
      std::make_tuple("day7/input_part1_test1.txt", 4, 32),
      std::make_tuple("day7/input_part2_test1.txt", 0, 126),
      std::make_tuple("day7/input_part2_test2.txt", 0, 190),
      std::make_tuple("day7/input.txt", 233, 421550)
    }));

  auto res = day7::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day7::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day7::part2(res) == expectedPart2);
  }
}