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

#**************************************************************************************************
# Set variable ************************************************************************************
SET(SOURCES

)

#**************************************************************************************************
# Set compiler ************************************************************************************
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_compile_options(/std:c++17)
else()
  add_compile_options(-std=c++2a -fPIC -O3)
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

SET(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/catch2-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day1-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day2-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day3-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day4-catch2.cpp
)

add_executable(unit-test ${TEST_SOURCES} ${SOURCES})
target_link_libraries(unit-test PRIVATE Catch2::Catch2)

add_executable(benchmark ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE fmt::fmt)

add_custom_target(test
  COMMAND unit-test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/input
)
