#include <tuple>
#include <iostream>

#include <catch2/catch.hpp>

#include "day5/day5.hpp"

TEST_CASE("AoC2020 Day5", "[day5]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE(table<std::string, size_t, long long>({
      std::make_tuple("day5/input_part1_test1.txt", 820, -1),
      std::make_tuple("day5/input.txt", 901, 661)
    }));

  std::vector<int> res = day5::parseInputFile(filename);

  SECTION("Part1 : " + filename) {
    CHECK(day5::part1(res) == expectedPart1);
  }
  SECTION("Part2 : " + filename) {
    CHECK(day5::part2(res) == expectedPart2);
  }
}