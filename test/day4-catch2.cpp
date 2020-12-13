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

  SECTION("Separated : " + filename) {
    auto res = day4::parseInputFile(filename);
    CHECK(day4::part1(res) == expectedPart1);
    CHECK(day4::part2(res) == expectedPart2);
  }
  SECTION("All in one : " + filename) {
    auto [part1, part2] = day4::allInOne(filename);
    CHECK(part1 == expectedPart1);
    CHECK(part1 == expectedPart1);
  }
}