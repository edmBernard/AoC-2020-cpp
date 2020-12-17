
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>

namespace day17 {

void showGrid(const std::vector<uint8_t> &grid, int width, int height) {
  std::cout << std::endl;
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (grid[y * width + x] > 0) {
        std::cout << "# ";
      } else {
        std::cout << ". ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


size_t part1(const std::tuple<std::vector<uint8_t>, int, int> &input) {
  const auto &[grid, width, height] = input;

  std::map<std::array<int, 3>, int8_t> previousGrid;
  for (int i = 0; i < grid.size(); ++i) {
    if (grid[i] == 1) {
      previousGrid[{i % width, i / width, 0}] = 1;
    }
  }

  std::map<std::array<int, 3>, int8_t> activeNeighbors;

  for (int notUsed = 0; notUsed < 6; ++notUsed) {

    for (const auto& [cube, states] : previousGrid) {

      if (states == 0) {
        continue;
      }

      const auto& [x,y,z] = cube;
      // dilate all active cube
      activeNeighbors[cube] = activeNeighbors[cube] - 1;
        int ww = 0;
        for (int zz = -1; zz < 2; ++zz) {
          for (int yy = -1; yy < 2; ++yy) {
            for (int xx = -1; xx < 2; ++xx) {
              const std::array<int, 3> neighborCube{xx + x, yy + y, zz + z};
              if (activeNeighbors.count(neighborCube)) {
                activeNeighbors[neighborCube] += 1;
              } else {
                activeNeighbors.emplace(neighborCube, 1);
              }
            }
          }
        }
    }

    for (const auto& [cube, neighbors] : activeNeighbors) {
      if (previousGrid.count(cube) && previousGrid[cube] == 1 && (neighbors < 2 || neighbors > 3)) {
        previousGrid[cube] = 0;
      } else if (neighbors == 3) {
        previousGrid[cube] = 1;
      }
    }

    activeNeighbors.clear();
  }

  size_t count = 0;
  for (const auto& [cube, states] : previousGrid) {
    if (states == 1) {
      count += 1;
    }
  }
  return count;
}


size_t part2(const std::tuple<std::vector<uint8_t>, int, int> &input) {
  const auto &[grid, width, height] = input;

  std::map<std::array<int, 4>, int8_t> previousGrid;
  for (int i = 0; i < grid.size(); ++i) {
    if (grid[i] == 1) {
      previousGrid[{i % width, i / width, 0, 0}] = 1;
    }
  }

  std::map<std::array<int, 4>, int8_t> activeNeighbors;

  for (int notUsed = 0; notUsed < 6; ++notUsed) {

    for (const auto& [cube, states] : previousGrid) {

      if (states == 0) {
        continue;
      }

      const auto& [x,y,z,w] = cube;
      // dilate all active cube
      activeNeighbors[cube] = activeNeighbors[cube] - 1;
      for (int ww = -1; ww < 2; ++ww) {
        for (int zz = -1; zz < 2; ++zz) {
          for (int yy = -1; yy < 2; ++yy) {
            for (int xx = -1; xx < 2; ++xx) {
              const std::array<int, 4> neighborCube{xx + x, yy + y, zz + z, ww + w};
              if (activeNeighbors.count(neighborCube)) {
                activeNeighbors[neighborCube] += 1;
              } else {
                activeNeighbors.emplace(neighborCube, 1);
              }
            }
          }
        }
      }
    }

    for (const auto& [cube, neighbors] : activeNeighbors) {
      if (previousGrid.count(cube) && previousGrid[cube] == 1 && (neighbors < 2 || neighbors > 3)) {
        previousGrid[cube] = 0;
      } else if (neighbors == 3) {
        previousGrid[cube] = 1;
      }
    }

    activeNeighbors.clear();
  }

  size_t count = 0;
  for (const auto& [cube, states] : previousGrid) {
    if (states == 1) {
      count += 1;
    }
  }
  return count;
}

std::tuple<std::vector<uint8_t>, int, int> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  int width = 0;
  int height = 0;
  std::vector<uint8_t> grid;
  std::string line;
  while (infile >> line) {
    for (char i : line) {
      if (i == '.') {
        grid.push_back(0);
      } else if (i == '#') {
        grid.push_back(1);
      }
    }
  }
  width = line.size();
  height = grid.size() / width;

  return {grid, width, height};
}

} // namespace day17