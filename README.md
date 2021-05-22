# AoC-2020
My Code for [Advent of Code 2020](https://adventofcode.com/2020)

## Dependencies

We use [vcpkg](https://github.com/Microsoft/vcpkg) to manage dependencies

This project depend on:
- [catch2](https://github.com/catchorg/Catch2): A modern, header-only test framework for unit testing.
- [fmt](https://fmt.dev/latest/index.html): A modern formatting library

```
./vcpkg install catch2 fmt
```

## Build instructions

```bash
mkdir build
cd build
# configure make with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

## Run Test

```bash
cmake --build . --config Release --target test
```

## Run Benchmark

```bash
cmake --build . --config Release --target benchmark
```

```
Day1     : 0.15 ms
Day2     : 1.03 ms
Day3     : 0.33 ms
Day4     : 1.79 ms
Day5     : 0.38 ms
Day6     : 0.41 ms
Day7     : 12.16 ms
Day8     : 2.11 ms
Day9     : 0.60 ms
Day10    : 0.12 ms
Day11    : 8.37 ms
Day12    : 0.30 ms
Day13    : 0.12 ms
Day14    : 23.77 ms
Day16    : 1.00 ms
Day17    : 84.78 ms
Day18    : 1.00 ms
Day19    : 2.41 ms
Total duration per run : 138.41 ms

Day15    : 552.23 ms // not take in account, too long
```