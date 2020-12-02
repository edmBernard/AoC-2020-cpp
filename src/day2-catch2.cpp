#include <tuple>
#include <iostream>

#include "day2/day2.hpp"
#include <catch2/catch.hpp>

TEST_CASE("AoC2020 Day2", "[day2]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, size_t>({
      std::make_tuple("day2/input_part1_test1.txt", 2, 1),
      std::make_tuple("day2/input.txt", 580, 611)
    }));

  std::vector<std::tuple<int, int, char, std::string>> elementList = day2::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day2::part1(elementList) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day2::part2(elementList) == expectedPart2);
  }
}