
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
      : grid(grid) {
  }

  bool isInside(int64_t x, int64_t y) const {
    return refX + x >= 0 && refY + y >= 0 && refX + x < grid[0].size() && refY + y < grid.size();
  }

  int operator()(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return 0;
    }
    return grid[refY + y][refX + x];
  }

  int occupied(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return 0;
    }
    const int occupied = grid[refY + y][refX + x];
    return occupied > 0 ? occupied : 0;
  }

  int seenOccupied(int64_t dirx, int64_t diry) const {
    int64_t x = dirx;
    int64_t y = diry;
    while (isInside(x, y)) {
      if (this->operator()(x, y) > 0) {
        return 1;
      }
      if (this->operator()(x, y) == 0) {
        return 0;
      }
      x += dirx;
      y += diry;
    }
    return 0;
  }

  int64_t refX = 0;
  int64_t refY = 0;

private:
  std::vector<std::vector<int>> &grid;
};

size_t part1(const std::vector<std::vector<int>> &grid) {
  std::vector<std::vector<int>> previousGrid(grid.begin(), grid.end());
  std::vector<std::vector<int>> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor Acc(previousGrid);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (Acc.refY = 0; Acc.refY < previousGrid.size(); Acc.refY++) {
      for (Acc.refX = 0; Acc.refX < previousGrid[0].size(); Acc.refX++) {

        if (Acc(0, 0) < 0) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = Acc.occupied(-1, -1) + Acc.occupied(0, -1) + Acc.occupied(1, -1) + Acc.occupied(-1, 0) + Acc.occupied(1, 0) + Acc.occupied(-1, 1) + Acc.occupied(0, 1) + Acc.occupied(1, 1);

        if (Acc(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[Acc.refY][Acc.refX] = 1;
          haveChanged = true;
          continue;
        }

        if (Acc(0, 0) == 1 && occupiedNeighbour > 3) {
          // if occupied seat
          nextGrid[Acc.refY][Acc.refX] = 0;
          haveChanged = true;
          continue;
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
      count += elem > 0 ? 1 : 0;
    }
  }
  return count;
}

size_t part2(const std::vector<std::vector<int>> &grid) {
  std::vector<std::vector<int>> previousGrid(grid.begin(), grid.end());
  std::vector<std::vector<int>> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor Acc(previousGrid);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (Acc.refY = 0; Acc.refY < previousGrid.size(); Acc.refY++) {
      for (Acc.refX = 0; Acc.refX < previousGrid[0].size(); Acc.refX++) {

        if (Acc(0, 0) < 0) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = Acc.seenOccupied(-1, -1) + Acc.seenOccupied(0, -1) + Acc.seenOccupied(1, -1) + Acc.seenOccupied(-1, 0) + Acc.seenOccupied(1, 0) + Acc.seenOccupied(-1, 1) + Acc.seenOccupied(0, 1) + Acc.seenOccupied(1, 1);

        if (Acc(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[Acc.refY][Acc.refX] = 1;
          haveChanged = true;
          continue;
        }

        if (Acc(0, 0) == 1 && occupiedNeighbour > 4) {
          // if occupied seat
          nextGrid[Acc.refY][Acc.refX] = 0;
          haveChanged = true;
          continue;
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
      count += elem > 0 ? 1 : 0;
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