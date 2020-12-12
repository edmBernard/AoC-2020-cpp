
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace day11 {

void showGrid(const std::vector<int8_t> &grid, int width, int height) {
  std::cout << std::endl;
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (grid[y * width + x] >= 0) {
        std::cout << grid[y * width + x] << " ";
      } else {
        std::cout << ". ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


size_t processLoop(const std::tuple<int, int, std::vector<int8_t>> &board, auto getNeighbour, int maxNeighbour) {
  const auto &[width, height, grid] = board;

  std::vector<int8_t> mutgrid(grid.begin(), grid.end());

  std::vector<size_t> seats;
  seats.reserve(mutgrid.size());
  std::vector<std::vector<size_t>> neighbours;
  neighbours.reserve(mutgrid.size());
  int rowOffset = width;
  int columnOffset = 1;

  for (size_t i = 0; i < mutgrid.size(); ++i) {
    if (mutgrid[i] == -1) {
      continue;
    }

    seats.push_back(i);

    std::vector<size_t> temp;
    temp.reserve(8);

    if (auto idx = getNeighbour(i, 1, 0, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, 1, 1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, 0, 1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, -1, 1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, -1, 0, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, -1, -1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, 0, -1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }
    if (auto idx = getNeighbour(i, 1, -1, grid, width, height); idx != 0) {
      temp.push_back(idx);
    }

    neighbours.push_back(temp);
  }

  std::vector<size_t> toChange;
  bool haveChanged = true;
  int unchangedSeat = 0;
  while (haveChanged) {
    haveChanged = false;

    for (size_t i = unchangedSeat; i < seats.size(); ++i) {
      const size_t idx = seats[i];

      int occupiedNeighbour = 0;
      for (const auto & nidx : neighbours[i]) {
        occupiedNeighbour += (mutgrid[nidx] == 1);
      }

      if ((mutgrid[idx] == 0 && occupiedNeighbour == 0) || (mutgrid[idx] == 1 && occupiedNeighbour > maxNeighbour)) {
        toChange.push_back(idx);
      } else {
        // /!\ It work for our case but not sure it's accurate, We consider a pixel that don't change will not change anymore.
        // I move all unchanged index at the begining of the seats list then I skip these index in the iteration
        std::swap(seats[i], seats[unchangedSeat]);
        std::swap(neighbours[i], neighbours[unchangedSeat]);
        ++unchangedSeat;
      }
    }

    for (const auto &idx : toChange) {
      // inverse state of seat in to change
      mutgrid[idx] = (mutgrid[idx] + 1) & 1;
    }
    haveChanged = toChange.size() != 0;
    toChange.clear();
  }

  size_t count = 0;
  for (const auto &idx : seats) {
    count += mutgrid[idx] == 1 ? 1 : 0;
  }
  return count;
}

size_t seatNear(size_t idx, int64_t offsetx, int64_t offsety, const std::vector<int8_t>& grid, int width, int height) {
  // we don't need to check border because we add padding around the grid
  if (grid[idx + offsetx + offsety * width] == 0) {
    return idx + offsetx + offsety * width;
  }
  return 0;
}


size_t part1(const std::tuple<int, int, std::vector<int8_t>> &board) {
  return processLoop(board, seatNear, 3);
}

size_t seatInSight(size_t idx, int64_t dirx, int64_t diry, const std::vector<int8_t>& grid, int width, int height) {
  int refx = idx % width;
  int refy = idx / width;
  auto isInside = [=](int x, int y) {return refx + x >= 0 & refy + y >= 0 & refx + x < width & refy + y < height; };
  for (int64_t x = dirx, y = diry; isInside(x, y); x += dirx, y += diry) {
    if (grid[(refy + y) * width + refx + x] != -1) {
      return (refy + y) * width + refx + x;
    }
  }
  return 0;
}

size_t part2(const std::tuple<int, int, std::vector<int8_t>> &board) {
  return processLoop(board, seatInSight, 4);
}

std::tuple<int, int, std::vector<int8_t>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  int width = 0;
  int height = 0;
  std::vector<int8_t> grid;
  std::string line;
  while (infile >> line) {

    grid.push_back(-1); // add padding to remove boundary check
    for (char i : line) {
      if (i == '.') {
        grid.push_back(-1);
      } else if (i == 'L') {
        grid.push_back(0);
      } else if (i == '#') {
        grid.push_back(1);
      }
    }
    grid.push_back(-1);
  }
  width = line.size() + 2;
  height = grid.size() / width + 2;

  std::vector<int8_t> fullFloorLine(width, -1);
  // add padding, one line before and one line after
  grid.insert(grid.begin(), fullFloorLine.begin(), fullFloorLine.end());
  grid.insert(grid.end(), fullFloorLine.begin(), fullFloorLine.end());

  return {width, height, grid};
}

} // namespace day11