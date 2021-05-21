#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day18/day18.hpp"

TEST_CASE("AoC2020 Day18", "[day18]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day18/input_part1_test1.txt", 71, 231),
      std::make_tuple("day18/input_part1_test2.txt", 51, 51),
      std::make_tuple("day18/input_part1_test3.txt", 13632, 23340),
      std::make_tuple("day18/input.txt", 1408133923393, 314455761823725)
    }));

  auto res = day18::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day18::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day18::part2(res) == expectedPart2);
  }
}