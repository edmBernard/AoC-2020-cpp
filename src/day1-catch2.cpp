#include <tuple>

#include <catch2/catch.hpp>
#include "day1/day1.hpp"

TEST_CASE("AoC2020 Day1", "[day1]") {

  auto [filename, expectedPart1, expectedPart2] = GENERATE( table<std::string, size_t, size_t>({
      std::make_tuple("day1/input_part1_test1.txt", 514579, 241861950),
      std::make_tuple("day1/input.txt", 381699, 111605670)
    } ) );

  std::vector<size_t> numberList = parseInputFile(filename);

  SECTION("Part1") {
    CHECK(find2Sum(numberList) == expectedPart1);
  }
  SECTION("Part2") {
    CHECK(find3Sum(numberList) == expectedPart2);
  }

}