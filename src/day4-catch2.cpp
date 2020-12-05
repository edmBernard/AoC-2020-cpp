#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day4/day4.hpp"

TEST_CASE("AoC2020 Day4", "[day4]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, long long>({
      std::make_tuple("day4/input_part1_test1.txt", 2, 2),
      std::make_tuple("day4/input_part2_test1.txt", 4, 4),
      std::make_tuple("day4/input_part2_test2.txt", 4, 0),
      std::make_tuple("day4/input.txt", 260, 153)
    }));

  auto res = day4::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day4::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day4::part2(res) == expectedPart2);
  }
}