
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

class GridAccessor3D {
public:
  GridAccessor3D(std::vector<uint8_t> &grid, int sizeX, int sizeY, int sizeZ)
      : grid(grid), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {
  }

  inline bool isInside(int64_t x, int64_t y, int64_t z) const {
    return (refX + x >= 0 & refX + x < sizeX &
            refY + y >= 0 & refY + y < sizeY &
            refZ + z >= 0 & refZ + z < sizeZ);
  }

  //! Access operator without boundary check
  const uint8_t &operator()(int64_t x, int64_t y, int64_t z) const {
    return grid[(refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  //! Access operator without boundary check
  uint8_t &operator()(int64_t x, int64_t y, int64_t z) {
    return grid[(refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  //! Access operator with boundary check
  const uint8_t &at(int64_t x, int64_t y, int64_t z) const {
    if (!isInside(x, y, z)) {
      throw std::runtime_error("get outside the allocated space");
    }
    return grid[(refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  size_t count() const {
    size_t count = 0;
    for (auto elem : grid) {
      count += elem;
    }
    return count;
  }

  int64_t refX = 0;
  int64_t refY = 0;
  int64_t refZ = 0;
  const size_t sizeX;
  const size_t sizeY;
  const size_t sizeZ;

private:
  std::vector<uint8_t> &grid;
};

class GridAccessor4D {
public:
  GridAccessor4D(std::vector<uint8_t> &grid, int sizeX, int sizeY, int sizeZ, int sizeW)
      : grid(grid), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW) {
  }

  inline bool isInside(int64_t x, int64_t y, int64_t z, int64_t w) const {
    return (refX + x >= 0 & refX + x < sizeX &
            refY + y >= 0 & refY + y < sizeY &
            refZ + z >= 0 & refZ + z < sizeZ &
            refW + w >= 0 & refW + w < sizeW);
  }

  //! Access operator without boundary check
  const uint8_t &operator()(int64_t x, int64_t y, int64_t z, int64_t w) const {
    return grid[(refW + w) * sizeW * sizeZ * sizeY+ (refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  //! Access operator without boundary check
  uint8_t &operator()(int64_t x, int64_t y, int64_t z, int64_t w) {
    return grid[(refW + w) * sizeW * sizeZ * sizeY+ (refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  //! Access operator with boundary check
  const uint8_t &at(int64_t x, int64_t y, int64_t z, int64_t w) const {
    if (!isInside(x, y, z, w)) {
      throw std::runtime_error("get outside the allocated space");
    }
    return grid[(refW + w) * sizeW * sizeZ * sizeY+ (refZ + z) * sizeZ * sizeY + (refY + y) * sizeY + refX + x];
  }

  size_t count() const {
    size_t count = 0;
    for (auto elem : grid) {
      count += elem;
    }
    return count;
  }

  int64_t refX = 0;
  int64_t refY = 0;
  int64_t refZ = 0;
  int64_t refW = 0;
  const size_t sizeX;
  const size_t sizeY;
  const size_t sizeZ;
  const size_t sizeW;

private:
  std::vector<uint8_t> &grid;
};

size_t part1(const std::tuple<std::vector<uint8_t>, int, int> &input) {
  const auto &[grid, width, height] = input;

  const size_t sizeX = 100;
  const size_t sizeY = 100;
  const size_t sizeZ = 100;
  const size_t offset = 50;

  std::vector<uint8_t> previousGrid(sizeX*sizeY*sizeZ, 0);
  GridAccessor3D prev(previousGrid, sizeX, sizeY, sizeZ);
  prev.refX = offset;
  prev.refY = offset;
  prev.refZ = offset;

  for (int i = 0; i < grid.size(); ++i) {
    prev(i % width, i / width, 0) = grid[i];
  }

  std::vector<uint8_t> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor3D next(nextGrid, sizeX, sizeY, sizeZ);

  for (int notUsed = 0; notUsed < 6; ++notUsed) {

    for (prev.refZ = 1; prev.refZ < prev.sizeZ-1; ++prev.refZ) {
      for (prev.refY = 1; prev.refY < prev.sizeY-1; ++prev.refY) {
        for (prev.refX = 1; prev.refX < prev.sizeX-1; ++prev.refX) {

          int activeNeighbors = -prev.at(0, 0, 0);
          for (int zz = -1; zz < 2; ++zz) {
            for (int yy = -1; yy < 2; ++yy) {
              for (int xx = -1; xx < 2; ++xx) {
                activeNeighbors += prev.at(xx, yy, zz);
              }
            }
          }
          // std::cout << "activeNeighbors: " << activeNeighbors << std::endl;

          if (prev(0, 0, 0) == 1 && (activeNeighbors < 2 || activeNeighbors > 3)) {
            next(prev.refX, prev.refY, prev.refZ) = 0;
          } else if (prev(0, 0, 0) == 0 && activeNeighbors == 3) {
            next(prev.refX, prev.refY, prev.refZ) = 1;
          }
        }
      }
    }
    previousGrid = nextGrid;
  }

  return prev.count();

}


size_t part2(const std::tuple<std::vector<uint8_t>, int, int> &input) {
  // got luky it work on it I should use a set and only store active point but no motivation
 const auto &[grid, width, height] = input;

  std::set<std::array<int64_t, 4>> previousGrid;
  for (int64_t i = 0; i < grid.size(); ++i) {
    if (grid[i] == 1) {
      previousGrid.insert({i % width, i / width, 0, 0});
    }
  }

  std::map<std::array<int64_t, 4>, int> activeNeighbors;

  for (int notUsed = 0; notUsed < 6; ++notUsed) {

    for (const auto& activeCube : previousGrid) {

      const auto& [x,y,z,w] = activeCube;
      // dilate all active cube
      activeNeighbors[{x, y, z, w}] = activeNeighbors[{x, y, z, w}] - 1;
      for (int ww = -1; ww < 2; ++ww) {
        for (int zz = -1; zz < 2; ++zz) {
          for (int yy = -1; yy < 2; ++yy) {
            for (int xx = -1; xx < 2; ++xx) {
              if (activeNeighbors.count({xx + x, yy + y, zz + z, ww + w})) {
                activeNeighbors[{xx + x, yy + y, zz + z, ww + w}] += 1;
              } else {
                activeNeighbors[{xx + x, yy + y, zz + z, ww + w}] = 1;
              }
            }
          }
        }
      }
    }

    for (const auto& [cube, neighbors] : activeNeighbors) {
      if (previousGrid.count(cube) && (neighbors < 2 || neighbors > 3)) {
        previousGrid.erase(cube);
      } else if (!previousGrid.count(cube) && neighbors == 3) {
        previousGrid.insert(cube);
      }
    }

    activeNeighbors.clear();
  }

  return previousGrid.size();
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