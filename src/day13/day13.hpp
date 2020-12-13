
#pragma once

#include <algorithm>
#include <charconv>
#include <exception>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <numeric>

namespace day13 {

size_t part1(const std::tuple<int, std::vector<int>> &inputs) {
  const auto& [timestamp, busIDs] = inputs;

  int nextBusTimestamp = timestamp * 2;
  int nextBusID = 0;
  for (int id : busIDs) {
    if (id == -1) {
      continue;
    }
    int nextStop = (timestamp + id -1) / id * id;
    if (nextStop < nextBusTimestamp) {
      nextBusTimestamp = nextStop;
      nextBusID = id;
    }
  }
  return (nextBusTimestamp - timestamp) * nextBusID;
}

int64_t findEi(const std::vector<int>& busIDs, size_t idx) {
  int64_t ni = 1;
  for (auto i : busIDs) {
    if (i != busIDs[idx]) {
      ni *= i;
    }
  }
  int64_t ei = ni;
  while (ei % busIDs[idx] != 1) {
    ei += ni;
  }
  return ei;
}


size_t part2(const std::tuple<int, std::vector<int>> &inputs) {
  // Chinese remainder theorem. cf. wikipedia
  const auto& [timestamp, busIDs] = inputs;

  std::vector<int> prunedBusIDs;
  std::vector<int> prunedOffset;
  int64_t n = 1;
  for (size_t idx = 0; idx < busIDs.size(); ++idx) {
    if (busIDs[idx] != -1) {
      prunedBusIDs.push_back(busIDs[idx]);
      prunedOffset.push_back(idx);
      n *= busIDs[idx];
    }
  }

  int64_t x = 0;
  for (size_t i = 0; i < prunedBusIDs.size(); ++i) {
    x += findEi(prunedBusIDs, i) * ((prunedBusIDs[i] - prunedOffset[i]) % prunedBusIDs[i]);
  }
  return x % n;
}

std::tuple<int, std::vector<int>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<int> busIDs;
  std::string line;
  int timestamp;
  // first line
  infile >> line;
  auto [p, ec] = std::from_chars(line.data(), line.data() + line.size(), timestamp);
  if (ec != std::errc()) {
    throw ec;
  }
  // second line
  infile >> line;
  std::stringstream ssLine(line);
  std::string id_s;
  int id_v;
  while (std::getline(ssLine, id_s, ',')) {
    auto [p, ec] = std::from_chars(id_s.data(), id_s.data() + id_s.size(), id_v);
    if (ec == std::errc()) {
      busIDs.push_back(id_v);
    } else {
      busIDs.push_back(-1);
    }
  }

  return {timestamp, busIDs};
}

} // namespace day13