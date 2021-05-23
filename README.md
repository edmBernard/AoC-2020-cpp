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

On my Linux with a `i5-4570` :

```
Day1     : 0.73 ms
Day2     : 0.62 ms
Day3     : 0.07 ms
Day4     : 1.50 ms
Day5     : 0.07 ms
Day6     : 0.10 ms
Day7     : 5.71 ms
Day8     : 3.05 ms
Day9     : 0.46 ms
Day10    : 0.03 ms
Day11    : 8.47 ms
Day12    : 0.07 ms
Day13    : 0.02 ms
Day14    : 14.20 ms
Day15    : 558.66 ms
Day16    : 0.73 ms
Day17    : 63.06 ms
Day18    : 0.83 ms
Day19    : 1.04 ms
Day23    : 221.29 ms
Day24    : 8.20 ms
Day25    : 25.54 ms
Total duration per run : 914.46 ms
```