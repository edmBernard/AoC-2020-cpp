
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace day11 {

void showGrid(const std::vector<std::vector<int>> &grid) {
  for (auto row : grid) {
    for (auto elem : row) {
      if (elem >= 0) {
        std::cout << elem << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

class GridAccessor {
public:
  GridAccessor(std::vector<int> &grid, int width, int height)
      : grid(grid), height(height), width(width) {
  }

  inline bool isInside(int64_t x, int64_t y) const {
    return refX + x >= 0 & refY + y >= 0 & refX + x < width & refY + y < height;
  }

  //! Access operator without boundary check
  const int &operator()(int64_t x, int64_t y) const {
    return grid[(refY + y) * width + refX + x];
  }

  //! Access operator without boundary check
  int &operator()(int64_t x, int64_t y) {
    return grid[(refY + y) * width + refX + x];
  }

  //! Access operator with boundary check
  const int &at(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return padding;
    }
    return grid[(refY + y) * width + refX + x];
  }

  int occupied(int64_t x, int64_t y) const {
    if (!isInside(x, y)) {
      return 0;
    }
    return grid[(refY + y) * width + refX + x] == 1 ? grid[(refY + y) * width + refX + x] : 0;
  }

  int occupiedWithoutCheck(int64_t x, int64_t y) const {
    return grid[(refY + y) * width + refX + x] == 1 ? grid[(refY + y) * width + refX + x] : 0;
  }

  int occupiedInSight(int64_t dirx, int64_t diry) const {
    for (int64_t x = dirx, y = diry; isInside(x, y); x += dirx, y += diry) {
      if (grid[(refY + y) * width + refX + x] != -1) {
        return grid[(refY + y) * width + refX + x];
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
  std::vector<int> &grid;
};

size_t part1(const std::tuple<int, int, std::vector<int>> &board) {
  const auto& [width, height, grid] = board;

  std::vector<int> previousGrid(grid.begin(), grid.end());
  std::vector<int> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor prev(previousGrid, width, height);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (prev.refY = 0; prev.refY < prev.height; ++prev.refY) {
      for (prev.refX = 0; prev.refX < prev.width; ++prev.refX) {

        if (prev(0, 0) == -1) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = prev.occupied(-1, -1) + prev.occupied(0, -1) + prev.occupied(1, -1) + prev.occupied(-1, 0) + prev.occupied(1, 0) + prev.occupied(-1, 1) + prev.occupied(0, 1) + prev.occupied(1, 1);

        if (prev(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[(prev.refY) * width + prev.refX] = 1;
          haveChanged = true;
        } else if (prev(0, 0) == 1 && occupiedNeighbour > 3) {
          // if occupied seat
          nextGrid[(prev.refY) * width + prev.refX] = 0;
          haveChanged = true;
        }
      }
    }

    previousGrid = nextGrid;
  }

  size_t count = 0;
  for (auto elem : previousGrid) {
    count += elem == 1 ? 1 : 0;
  }
  return count;
}

size_t part2(const std::tuple<int, int, std::vector<int>> &board) {
  const auto& [width, height, grid] = board;

  std::vector<int> previousGrid(grid.begin(), grid.end());
  std::vector<int> nextGrid(previousGrid.begin(), previousGrid.end());
  GridAccessor prev(previousGrid, width, height);

  bool haveChanged = true;
  while (haveChanged) {
    haveChanged = false;

    for (prev.refY = 0; prev.refY < prev.height; ++prev.refY) {
      for (prev.refX = 0; prev.refX < prev.width; ++prev.refX) {

        if (prev(0, 0) == -1) {
          // if no seat
          continue;
        }

        const int occupiedNeighbour = prev.occupiedInSight(-1, -1) + prev.occupiedInSight(0, -1) + prev.occupiedInSight(1, -1) + prev.occupiedInSight(-1, 0) + prev.occupiedInSight(1, 0) + prev.occupiedInSight(-1, 1) + prev.occupiedInSight(0, 1) + prev.occupiedInSight(1, 1);

        if (prev(0, 0) == 0 && occupiedNeighbour == 0) {
          // if not occupied seat
          nextGrid[(prev.refY) * width + prev.refX] = 1;
          haveChanged = true;
        } else if (prev(0, 0) == 1 && occupiedNeighbour > 4) {
          // if occupied seat
          nextGrid[(prev.refY) * width + prev.refX] = 0;
          haveChanged = true;
        }
      }
    }

    previousGrid = nextGrid;
  }

  size_t count = 0;
  for (auto elem : previousGrid) {
    count += elem == 1 ? 1 : 0;
  }
  return count;
}

std::tuple<int, int, std::vector<int>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  int width = 0;
  int height = 0;
  std::vector<int> grid;
  std::string line;
  while (infile >> line) {

    for (char i : line) {
      if (i == '.') {
        grid.push_back(-1);
      } else if (i == 'L') {
        grid.push_back(0);
      } else if (i == '#') {
        grid.push_back(1);
      }
    }
    if (width == 0) {
      width = grid.size();
    }
  }
  height = grid.size() / width;
  return {width, height, grid};
}

} // namespace day11