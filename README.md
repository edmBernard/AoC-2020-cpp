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
Day1     : 0.76 ms
Day2     : 0.57 ms
Day3     : 0.05 ms
Day4     : 1.47 ms
Day5     : 0.05 ms
Day6     : 0.09 ms
Day7     : 5.55 ms
Day8     : 2.25 ms
Day9     : 0.28 ms
Day10    : 0.01 ms
Day11    : 7.57 ms
Day12    : 0.05 ms
Day13    : 0.01 ms
Total duration per run : 18.71 ms
```