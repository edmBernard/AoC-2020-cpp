
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace day11 {

class GridAccessor {
public:
  GridAccessor(std::vector<std::vector<int>> &grid)
      : grid(grid), height(grid.size()), width(grid[0].size()) {
  }

  bool isInside(int64_t x, int64_t y) const {
    return refX + x >= 0 & refY + y >= 0 & refX + x < width & refY + y < height;
  }

  const int& operator()(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return padding;
    }
    return grid[refY + y][refX + x];
  }

  int& operator()(int64_t x, int64_t y) {
    return grid[refY + y][refX + x];
  }

  int occupied(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return 0;
    }
    const int occupied = grid[refY + y][refX + x];
    return occupied > 0 ? occupied : 0;
  }

  int occupiedInSight(int64_t dirx, int64_t diry) const {
    for (int64_t x = dirx, y = diry; isInside(x, y); x += dirx, y += diry) {
      if (this->operator()(x, y) != -1) {
        return this->operator()(x, y);
      }
    }
    return 0;
  }

  int64_t refX = 0;
  int64_t refY = 0;
  const size_t height;
  const size_t width;

private:
  const int padding = 0;
  std::vector<std::vector<int>> &grid;
};

size_t part1(const std::vector<std::vector<int>> &grid) {
  std::vector<std::vector<int>> previousGrid(grid.begin(), grid.end());
  std::vector<std::vector<int>> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor prev(previousGrid);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (prev.refY = 0; prev.refY < prev.height; ++prev.refY) {
      for (prev.refX = 0; prev.refX < prev.width; ++prev.refX) {

        if (prev(0, 0) < 0) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = prev.occupied(-1, -1) + prev.occupied(0, -1) + prev.occupied(1, -1) + prev.occupied(-1, 0) + prev.occupied(1, 0) + prev.occupied(-1, 1) + prev.occupied(0, 1) + prev.occupied(1, 1);

        if (prev(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[prev.refY][prev.refX] = 1;
          haveChanged = true;
        } else  if (prev(0, 0) == 1 && occupiedNeighbour > 3) {
          // if occupied seat
          nextGrid[prev.refY][prev.refX] = 0;
          haveChanged = true;
        }
      }
    }

    // std::cout << "grid " << std::endl;
    // for (auto row : nextGrid) {
    //   for (auto elem : row) {
    //     if (elem >= 0) {
    //       std::cout << elem << " ";
    //     } else {
    //       std::cout << "  ";
    //     }
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    previousGrid = nextGrid;

  }

  size_t count = 0;
  for (auto row : previousGrid) {
    for (auto elem : row) {
      count += elem == 1 ? 1 : 0;
    }
  }
  return count;
}

size_t part2(const std::vector<std::vector<int>> &grid) {
  std::vector<std::vector<int>> previousGrid(grid.begin(), grid.end());
  std::vector<std::vector<int>> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor prev(previousGrid);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (prev.refY = 0; prev.refY < prev.height; ++prev.refY) {
      for (prev.refX = 0; prev.refX < prev.width; ++prev.refX) {

        if (prev(0, 0) < 0) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = prev.occupiedInSight(-1, -1) + prev.occupiedInSight(0, -1) + prev.occupiedInSight(1, -1) + prev.occupiedInSight(-1, 0) + prev.occupiedInSight(1, 0) + prev.occupiedInSight(-1, 1) + prev.occupiedInSight(0, 1) + prev.occupiedInSight(1, 1);

        if (prev(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[prev.refY][prev.refX] = 1;
          haveChanged = true;
        } else if (prev(0, 0) == 1 && occupiedNeighbour > 4) {
          // if occupied seat
          nextGrid[prev.refY][prev.refX] = 0;
          haveChanged = true;
        }
      }
    }

    // std::cout << "grid " << std::endl;
    // for (auto row : nextGrid) {
    //   for (auto elem : row) {
    //     if (elem >= 0) {
    //       std::cout << elem << " ";
    //     } else {
    //       std::cout << "  ";
    //     }
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    previousGrid = nextGrid;
  }

  size_t count = 0;
  for (auto row : previousGrid) {
    for (auto elem : row) {
      count += elem == 1 ? 1 : 0;
    }
  }
  return count;
}

std::vector<std::vector<int>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::vector<std::vector<int>> grid;
  std::string line;
  while (infile >> line) {
    std::vector<int> row;
    for (char i : line) {
      if (i == '.') {
        row.push_back(-1);
      } else if (i == 'L') {
        row.push_back(0);
      } else if (i == '#') {
        row.push_back(1);
      }
    }
    grid.push_back(row);
  }
  return grid;
}

} // namespace day11