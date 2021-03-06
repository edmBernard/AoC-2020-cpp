project(AoC-2020)

#**************************************************************************************************
# General cMake settings
#**************************************************************************************************
cmake_minimum_required(VERSION 3.17)

option(USE_OPTIMIZED_VERSION "Switch to disable my try to have faster version" ON)
if (USE_OPTIMIZED_VERSION)
  add_compile_definitions(USE_OPTIMIZED_VERSION)
endif()

#**************************************************************************************************
# Find Package ************************************************************************************
find_package(Catch2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

#**************************************************************************************************
# Include *****************************************************************************************
include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)

#**************************************************************************************************
# Set variable ************************************************************************************
SET(SOURCES

)

#**************************************************************************************************
# Set compiler ************************************************************************************
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_compile_options(/std:c++latest /02 /Ot /Oy)
else()
  add_compile_options(-std=c++2a -fPIC -O3 -fno-omit-frame-pointer)
endif()

#**************************************************************************************************
# Linker ******************************************************************************************


#**************************************************************************************************
# Build Example
#**************************************************************************************************
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day6)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day7)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day8)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day9)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day10)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day11)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day12)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day13)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day14)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day15)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day16)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day17)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day18)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day19)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day23)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day24)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day25)

SET(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test/catch2-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day1-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day2-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day3-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day4-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day5-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day6-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day7-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day8-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day9-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day10-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day11-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day12-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day13-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day14-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day15-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day16-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day17-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day18-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day19-catch2.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/test/day23-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day24-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/day25-catch2.cpp
)

add_executable(unit-test ${TEST_SOURCES} ${SOURCES})
target_link_libraries(unit-test PRIVATE Catch2::Catch2)

add_executable(unit-benchmark ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark.cpp)
target_link_libraries(unit-benchmark PRIVATE fmt::fmt)

add_custom_target(test
  COMMAND unit-test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/input
)

add_custom_target(benchmark
  COMMAND unit-benchmark
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/input
)
