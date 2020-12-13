
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

size_t part2(const std::tuple<int, std::vector<int>> &inputs) {
  const auto& [timestamp, busIDs] = inputs;

  auto max = std::max_element(busIDs.begin(), busIDs.end());
  int64_t timestampTarget = - (max - busIDs.begin());
  std::cout << "std::numeric_limits<int64_t>::max(): " << std::numeric_limits<int64_t>::max() << std::endl;

  std::vector<int> prunedBusIDs;
  std::vector<int> prunedOffset;
  for (size_t idx = 0; idx < busIDs.size(); ++idx) {
    if (busIDs[idx] != -1) {
      prunedBusIDs.push_back(busIDs[idx]);
      prunedOffset.push_back(idx);
    }
  }


  bool notValid = true;
  while (notValid) {
    notValid = false;
    timestampTarget += *max;
    for (size_t i = 0; i < prunedOffset.size(); ++i) {
      const int id = prunedBusIDs[i];
      const int offset = prunedOffset[i];
      if ((timestampTarget+offset)%id != 0) {
        notValid = true;
      }
    }
    if (timestampTarget % 10000 == 0) {
      std::cout << "timestampTarget: " << timestampTarget << std::endl;
    }
    if (timestampTarget > std::numeric_limits<int64_t>::max() - 2 * (*max)) {
      break;
    }
  }
  return timestampTarget;
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